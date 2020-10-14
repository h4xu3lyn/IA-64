#ifndef _OSLOAD_H
#define _OSLOAD_H

struct os_proc
{
	int	has_rtld;
	int	phdr_count;
	ADDR	phdr_addr;
	ADDR	rtld_base;
	ADDR	proc_entry;
	unsigned int ehdr_flags;
	ADDR	aout_base;
	ADDR	aout_phdr;
};

int	os_elf32_abi(char *, Elf32_Ehdr *, int);
int	os_elf64_abi(char *, Elf64_Ehdr *, int);
ADDR	os_rtld32_data(Elf32_Phdr *);
ADDR	os_rtld32_text(Elf32_Phdr *);
ADDR	os_rtld64_data(Elf64_Phdr *);
ADDR	os_rtld64_text(Elf64_Phdr *);
int	os_setup_process(const char *, int, char **, struct os_proc *);

#endif
