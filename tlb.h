#ifndef _TLB_H_
#define	_TLB_H_

#include "simmem.h"

#define NDTRS	 16
#define NITRS	 16
#define NDTCS	128
#define NITCS	128
#define UNIMPL_VA_LEN	(61 - va_len)
#define BE_VA_MSB	(3 + UNIMPL_VA_LEN)
#define UNIMPL_PA_LEN	(63 - pa_len)
#define BE_PA_MSB	(1 + UNIMPL_PA_LEN)

#define unimplVirtAddr(va)	\
		(UNIMPL_VA_LEN && BitfX(va,3,UNIMPL_VA_LEN) !=	\
			(BitfX(va,BE_VA_MSB,1) ? ONES(UNIMPL_VA_LEN) : 0))

#define unimplPhysAddr(pa)	\
		(UNIMPL_PA_LEN && BitfX(pa,1,UNIMPL_PA_LEN))

#define unimplAddr(addr)	((PSR_IT && unimplVirtAddr(addr)) ||	\
				(!PSR_IT && unimplPhysAddr(addr)))

#define sxtUnimplVA(va)		\
		(!UNIMPL_VA_LEN ? va :	\
		    (BitfX(va,BE_VA_MSB,1) ?		\
			(va | (ADDR)ONES(UNIMPL_VA_LEN) << va_len) :	\
			(va & ~((ADDR)ONES(UNIMPL_VA_LEN) << va_len)) 	\
		    )	\
		)

#define zxtUnimplPA(pa)		\
		(!UNIMPL_PA_LEN ? pa	\
				: pa & ~((ADDR)ONES(UNIMPL_PA_LEN) << pa_len))

#define DBGREGS

typedef struct TlbEntry_t {
    ADDR vpn, ppn, psm;
    unsigned rid;
    unsigned ed:  1;
    unsigned ar:  3;
    unsigned pl:  2;
    unsigned d:   1;
    unsigned a:   1;
    unsigned ma:  4;
    unsigned p:   1;
    unsigned pad:19;
    unsigned key:24;
#ifdef DBGREGS
    unsigned dbg: 1;
#endif
    unsigned quickchk;
    unsigned when;

    struct TlbEntry_t* next;
} TlbEntry;

extern unsigned va_len, pa_len, rid_len, key_len;

void tlbInit(void);
BOOL unimplPageSize(unsigned ps);
int dtlbLookup(ADDR va, unsigned size, Accesstype atype, unsigned pl,
	       BOOL virtual, ADDR *pa);
int specLookup(ADDR va, unsigned size, Accesstype atype, ADDR *pa);
int probeLookup(ADDR va, Accesstype atype, unsigned pl);
REG takLookup(ADDR va);
int vhptLookup(ADDR va, ADDR *pa);
int dbptLookup(ADDR va, ADDR *pa);
BOOL itlbLookup(ADDR va, BOOL virtual, ADDR *pa);
BOOL dtlbMLookup(ADDR va, int at, unsigned pl, BOOL virtual, ADDR *pa);
BOOL itlbMLookup(ADDR va, BOOL virtual, ADDR *pa);
BOOL dtrInsert(unsigned slot, ADDR tpa);
BOOL itrInsert(unsigned slot, ADDR tpa);
void dtrPurge(ADDR va, unsigned range);
void itrPurge(ADDR va, unsigned range);
BOOL dtcInsert(unsigned when, ADDR tpa);
BOOL itcInsert(unsigned when, ADDR tpa);
void tcPurge(ADDR va, unsigned range);
void tcEntryPurge(ADDR va);
ADDR thash(ADDR va);
ADDR ttag(ADDR va);
void epcCheck(BYTE *pl);
int vhptLookup(ADDR va, ADDR *pa);
BOOL vmswCheck(BOOL virtual);

#endif
