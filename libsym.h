#ifndef _LIBSYM_H
#define _LIBSYM_H

typedef struct {
    char *name;			/* symbol name */
    void *extra;		/* pointer to extra symbol info */
    unsigned long long addr;	/* value (address) associated with symbol */
} Symbol, *SymbolPtr;

typedef struct symTableStructure *SymTablePtr;
typedef int (*PSCF)(const SymbolPtr sym, const void *cmpArg);

extern SymTablePtr defaultSymTable;

SymbolPtr symAddrSearch(SymTablePtr t, unsigned long long addr, PSCF cmpFn,
			const void *cmpArg);
#define symAddrtoAddr(addr, dist, cmpFn, cmpArg) \
	symAddrtoAddrX(defaultSymTable, addr, dist, cmpFn, cmpArg)
unsigned long long symAddrtoAddrX(SymTablePtr t, unsigned long long addr,
				  int dist, PSCF cmpFn, const void *cmpArg);
#define symInsert(name, addr, extra)	((void)symInsertX(defaultSymTable, name, addr, extra))
SymbolPtr symInsertX(SymTablePtr t, const char *name, unsigned long long addr,
		     void *extra);
#define symNametoAddr(name, paddr) symNametoAddrX(defaultSymTable, name, paddr)
BOOL symNametoAddrX(SymTablePtr t, const char *name, unsigned long long *paddr);
#define symNameLookup(name, paddr, extra) \
	symNameLookupX(defaultSymTable, name, paddr, extra)
BOOL symNameLookupX(SymTablePtr t, const char *name, unsigned long long *paddr,
		   void **extra);
void symAddrtoName(unsigned long long addr, char sname[], int rmdr, int add0x,
		   int width);
void symName(SymbolPtr s, unsigned long long addr, char sname[],
	     int rmdr, int add0x, int width);
void symAddrtoNameX(SymTablePtr t, unsigned long long addr, char sname[],
		    int rmdr, int add0x, int width, PSCF cmpFn,
		    const void *cmpArg);
#define symNextSymInit() symNextSymInitX(defaultSymTable)
void symNextSymInitX(SymTablePtr t);
#define symNextSym(sym) symNextSymX(defaultSymTable, sym)
BOOL symNextSymX(SymTablePtr t, SymbolPtr sym);
#define symDeleteAddr(saddr, eaddr) \
	symDeleteAddrX(defaultSymTable, saddr, eaddr)
void symDeleteAddrX(SymTablePtr t, unsigned long long saddr,
		    unsigned long long eaddr);
void symlDelete(void);
void symFreeTable(SymTablePtr t);
void symInit(void);
SymTablePtr symNewTable(void);

#endif
