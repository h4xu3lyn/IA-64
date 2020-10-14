#include <sys/time.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "std.h"
#include "types.h"
#include "state.h"

#include "freebsd/machdep.h"

int _close(int);
int _open(const char *, int, int);

CTR prof_insts = ~0ULL;
char *src_root;

#define	SKI_NFDS	20
int fdlimit;
int fdmap[SKI_NFDS];

void setFdmap(int fd1, int fd2)
{
	assert(0);
}

void profCnt(void)
{
	assert(0);
}

void saveOpenFiles(FILE *f)
{
}

void restoreOpenFile(char *name, unsigned flag, unsigned mode, unsigned offset)
{
}

int open(const char *path, int flags, int mode)
{
	int res, fd;

	if (!unixABI)
		return (_open(path, flags, mode));

	if (fdlimit == 0) {
		fdlimit = getdtablesize() - SKI_NFDS;
		if (fdlimit < 20) {
			fprintf(stderr, "FD table size underflow\n");
			abort();
		}
		dup2(0, fdlimit);
		dup2(1, fdlimit + 1);
		dup2(2, fdlimit + 2);
		fdmap[0] = fdmap[1] = fdmap[2] = 1;
		stdin->_file += fdlimit;
		stdout->_file += fdlimit;
		stderr->_file += fdlimit;
	}

	res = _open(path, flags, mode);
	if (res >= fdlimit) {
		_close(res);
		errno = EMFILE;
		return (-1);
	} else if (res == -1)
		return (res);

	fd = 0;
	while (fd < SKI_NFDS && fdmap[fd])
		fd++;
	if (fd == SKI_NFDS) {
		_close(res);
		errno = EMFILE;
		return (-1);
	}
	if (dup2(res, fd + fdlimit) == -1) {
		_close(res);
		errno = EMFILE;
		return (-1);
	}
	_close(res);
	fdmap[fd] = 1;
	return (fd + fdlimit);
}

int close(int fd)
{
	if (fd >= fdlimit && fdlimit != 0)
		fdmap[fd - fdlimit] = 0;
	_close(fd);
}