#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned char		BYTE;
typedef unsigned short		HWORD, IAWORD;
typedef unsigned		WORD, IADWORD;
typedef unsigned long long	DWORD, REG, ADDR, CTR;

typedef struct {
    DWORD left, right;
} QWORD;


typedef struct meminfo_s {
    ADDR startadr;
    unsigned numpgs;
    DWORD *mdata;
    struct meminfo_s *next;
} *Meminfo_p;

typedef enum {
    BRT_NONE, BRT_IPRELJUMP, BRT_IPRELCALL, BRT_INDJUMP, BRT_INDCALL, BRT_RET,
    BRT_INVALID
} BRTYPE;

#endif
