#include "std.h"
#include "bits.h"
#include "types.h"
#include "fields.h"
#include "ski.h"
#define NPROC 1
#include "program.h"
#include "libsym.h"
#include "libsrs.h"
#include "libcore.h"
#include "exportui.h"
#include "coreui.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *src_root;

#define FNAME_LEN	54
#define EMPTY_FILENAME	"???"
#define NOT_A_LINE	0xffffffff

#if defined HAVE_DWARF_SUPPORT

#include "bfd.h"

#include <sys/param.h>

#undef DEBUG_DWARF

extern PrgwMode prgwm;

ADDR text_base, unwind_base;


struct line_info
  {
    bfd_vma address;
    bfd_vma limit;
    const char *filename;
    const char *function;
    unsigned int line;		/* first line number */
    unsigned int num_lines;	/* number of lines to display */
    int valid;			/* is this info valid? */
  };

static int bfd_init_done;
static int found;	/* used when iterating over sections */

static asymbol **syms;	/* our local symbol table */
static int src_root_len;	/* how long is the prefix ? */
static bfd *cur_bfd;	/* holds the BFD state for a given executable */
static struct line_info cache;

#ifdef DEBUG_DWARF
static FILE *dump_fd;
#endif

void
fatal_error (char *msg)
{
  fprintf (stderr, "simulator-dwarf: %s", msg);
  exit (1);
}

void
find_in_section (bfd * bfd, asection * sect, PTR obj)
{
  struct line_info *info = obj;
  unsigned int last_line = 0, line;
  struct line_info first;
  bfd_vma vma, offset, i;
  const char *filename;
  const char *function;
  bfd_size_type size;

  if (info->valid)
    return;

  if ((bfd_get_section_flags (bfd, sect) & (SEC_CODE | SEC_ALLOC)) == 0)
    return;

  vma = bfd_get_section_vma (bfd, sect);
  size = bfd_section_size (bfd, sect);

  offset = info->address - vma;
  if (offset >= size)
    return;

  first.valid = 0;
  for (i = 0; i <= 8; i += 4, offset += 4)
    {
      found = bfd_find_nearest_line (bfd, sect, syms, offset,
				     &filename, &function, &line);
#ifdef DEBUG_DWARF
      fprintf (dump_fd,
	       "%llx -> sect=%s found=%d filename=%s function=%s line=%d\n",
	       vma + offset, sect->name, found, filename ? filename : "<none>",
	       function ? function : "<none>", line);
#endif
      if (found)
	{
	  if (!first.valid)
	    {
    	      first.valid = 1;
	      first.address = info->address;
	      first.filename = filename;
	      first.function = function;
	      first.line = line;
	      first.num_lines = 1;
	      first.limit = sect->size;
	      last_line = line;
	    }
	  if (line > last_line
	      && filename == first.filename && function == first.function)
	    last_line = line;
	}
    }

  if (!first.valid)
    return;

  while (offset < first.limit)
    {
      offset += 4;
      if ((offset & 0xf) > 8)
	offset += 16 - (offset & 0xf);
      found = bfd_find_nearest_line (bfd, sect, syms, offset,
				     &filename, &function, &line);

      if (!found || filename != first.filename || function != first.function)
	break;

      if (line != last_line)
	{
	  if (line > last_line)
	    {
#ifdef DEBUG_DWARF
	      fprintf (dump_fd, "line range = %u..%u\n", first.line, line - 1);
#endif
	      first.num_lines = line - first.line;
	    }
	  break;
	}
    }
  *info = first;
}

char *
read_source_lines (struct line_info *info, unsigned *count)
{
  static char *line = NULL;
  static size_t line_size = 0;
  static char *src_lines = 0;
  static size_t size = 0;
  unsigned int line_num = 0;
  const char *filename;
  ssize_t line_len = 0;
  size_t off;
  FILE *fp;
  int i;

  if (!info->filename)
    return "";

#ifdef DEBUG_DWARF
  fprintf (dump_fd, "displaying %s:%u-%u\n",
	   info->filename, info->line, info->line + info->num_lines - 1);
#endif

  filename = info->filename;
  if (src_root_len > 0)
    {
      size_t filename_len = strlen (info->filename);
      char *buf;

      buf = alloca (src_root_len + filename_len + 1);
      if (!buf)
	fatal_error ("Out of memory");

      memcpy (buf, src_root, src_root_len);
      memcpy (buf + src_root_len, info->filename, filename_len + 1);
      filename = buf;
    }
  fp = fopen (filename, "r");
  if (fp == NULL)
    return "";

  while (line_num < info->line
	 && (line_len = getline (&line, &line_size, fp)) >= 0)
    ++line_num;

  if (line_num != info->line)
    {
      cmdwPrint ("WARNING: Can't find line %d in %s\n", line, filename);
      return "";
    }

  off = 0;
  for (i = 0; i < info->num_lines; ++i)
    {
      if (*count >= 3)
	{
	  strcpy (line, "...\n");
	  line_len = 4;
	  i = info->num_lines;
	}
      if (off + line_len + 4 > size)
	{
	  size += 1024;
	  src_lines = realloc (src_lines, size);
	  if (!src_lines)
	    fatal_error ("Out of memory");
	}
      sprintf (src_lines + off, "%03u ", line_num + i);
      memcpy (src_lines + off + 4, line, line_len + 1);
      off += line_len + 4;
      ++*count;
      line_len = getline (&line, &line_size, fp);
      if (line_len < 0)
	break;
    }
  fclose (fp);
  return src_lines;
}

static int
get_source_info (ADDR addr, struct line_info *info)
{
  if (cur_bfd == NULL)
    return -1;

  if (cache.valid && (cache.address >> 4) == (addr >> 4))
    {
      *info = cache;
      return 0;
    }

  memset (info, 0, sizeof (*info));
  info->address = addr;
  bfd_map_over_sections (cur_bfd, find_in_section, info);

  if (info->valid)
    {
      cache = *info;
      return 0;
    }
  return -1;
}

char *
getSrcLines (ADDR ofs, unsigned *count)
{
  static struct line_info prev;
  struct line_info info, disp;
  int ret;

  *count = 0;

  if (prgwm == ASM)
    return "";

  cmdwSetStatus ("Reading debug info...");
  ret = get_source_info (ofs, &info);
  cmdwSetStatus ("");

  if (ret < 0)
    return "";

  disp = info;
  if (prev.valid && ofs > prev.address)
    {
      if (info.filename == prev.filename)
	{
	  if (info.line + info.num_lines <= prev.line + prev.num_lines)
	    return "";

	  disp.line = MAX (prev.line + prev.num_lines, info.line);
	  disp.num_lines = info.line + info.num_lines - disp.line;
	}
    }
  prev = info;
  return read_source_lines (&disp, count);
}

char *
getSrcName (ADDR ofs)
{
  static char fname[FNAME_LEN];
  struct line_info info;
  int l, offs;

  if (get_source_info (ofs, &info) < 0 || !info.filename)
    {
      strcpy (fname, EMPTY_FILENAME);
      return fname;
    }

  l = src_root_len + strlen (info.filename);
  if (l > FNAME_LEN - 1)
    {
      offs = l - (FNAME_LEN - 1 - 3);
      l = FNAME_LEN - 1 - 3;
      strcpy (fname + 3, info.filename + offs);
      fname[0] = fname[1] = fname[2] = '.';
    }
  else
    {
      if (src_root_len > 0)
	strncpy (fname, src_root, src_root_len);
      strcpy (fname + src_root_len, info.filename);
    }
  return fname;
}

static void
load_symbols (bfd * abfd)
{
  long storage;
  long symcount;

  if ((bfd_get_file_flags (abfd) & HAS_SYMS) == 0)
    return;

  storage = bfd_get_symtab_upper_bound (abfd);
  if (storage < 0)
    fatal_error ("can't get sym table size\n");
  syms = (asymbol **) malloc (storage);
  if (!syms)
    fatal_error ("malloc\n");

  symcount = bfd_canonicalize_symtab (abfd, syms);
  if (symcount < 0)
    fatal_error ("canonicalize\n");
#ifdef DEBUG_DWARF
  cmdwPrint ("symcount=%d\n", symcount);
#endif
}

#ifdef DEBUG_DWARF

static void
close_dump_fd (void)
{
  fclose (dump_fd);
}
#endif

static void
do_bfd_init (void)
{

  if (sizeof (bfd_vma) < sizeof (ADDR))
    {
      fprintf (stderr, "invalid bfd_vma size: check your bfd.h\n");
      exit (1);
    }

  bfd_init ();

  if (!bfd_set_default_target ("elf64-ia64-little"))
    fatal_error ("set_default_target");

  bfd_init_done = 1;

#ifdef DEBUG_DWARF
  dump_fd = fopen ("ski.log", "w");
  atexit (close_dump_fd);
#endif
 
  src_root_len = 0;
  if (src_root)
    src_root_len = strlen (src_root);
}

void
initDwUnitTbl (int fd)
{
  char **matching;
  bfd *bfd;
  int fd2;

  if (bfd_init_done == 0)
    do_bfd_init ();

  fd2 = dup (fd);
  if (fd2 == -1)
    fatal_error ("dup failed\n");
  lseek (fd2, 0, SEEK_SET);

  if (cur_bfd)
    {
      bfd_close (cur_bfd);
      cur_bfd = NULL;

      memset (&cache, 0, sizeof (cache));

      if (syms)
	free (syms);
      syms = NULL;
    }

  bfd = bfd_fdopenr ("", "default", fd2);
  if (bfd == NULL)
    fatal_error ("fdopenr\n");

  if (bfd_check_format (bfd, bfd_archive))
    fatal_error ("check_format");

  if (!bfd_check_format_matches (bfd, bfd_object, &matching))
    fatal_error ("check_format_matches");

  load_symbols (bfd);

  cur_bfd = bfd;
}

#else

char *
getSrcLines (ADDR ofs, unsigned *count)
{
  *count = 0;
  return "";
}

char *
getSrcName (ADDR ofs)
{
  static char fname[FNAME_LEN];
  strcpy (fname, EMPTY_FILENAME);
  return fname;
}

void
initDwUnitTbl (int fd)
{
}

#endif
