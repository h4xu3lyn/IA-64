#ifndef _DOS_H
#define _DOS_H

typedef struct {
    IAWORD exSignature;		/* EXE signature = 0x5A4D = "MZ" */
    IAWORD exExtraBytes;	/* # of bytes in last partial page in file */
    IAWORD exPages;		/* # of (512-byte) pages in file */
    IAWORD exRelocItems;	/* # of pointers in relocation table */
    IAWORD exHeaderSize;	/* size of file header, in (16-byte) paras */
    IAWORD exMinAlloc;		/* min amount of extra mem (in paras) */
    IAWORD exMaxAlloc;		/* max amount of extra mem (in paras) */
    IAWORD exInitSS;		/* initial SS register value (relocatable) */
    IAWORD exInitSP;		/* initial SP register value */
    IAWORD exCheckSum;		/* 1's complement, 16-bit sum */
    IAWORD exInitIP;		/* initial IP register value */
    IAWORD exInitCS;		/* initial CS register value (relocatable) */
    IAWORD exRelocTable;	/* file offset (in bytes) of reloc table */
    IAWORD exOverlay;		/* overlay management (0 for main prog) */
} EXEheader, *EXEheaderPtr;

typedef struct {
    IAWORD ip;
    IAWORD cs;
} IAvector, *IAvectorPtr;

typedef struct {
    IAWORD   pspInt20;		  /* Int 20h instruction */
    IAWORD   pspNextParagraph;	  /* segment addr of next paragraph */
    BYTE     rv1B;		  /* reserved */
    BYTE     pspDispatcher[5];	  /* long call to DOS */
    IAvector pspTerminateVector;  /* termination address (Int 22h) */
    IAvector pspControlCVector;   /* ctrl-c handler address (Int 23h) */
    IAvector pspCritErrorVector;  /* crit-error handler address (Int 24h) */
    IAWORD   rv11W[11];		  /* reserved */
    IAWORD   pspEnvironment;	  /* segment addr of environment */
    IAWORD   rv23W[23];		  /* reserved */
    BYTE     pspFCB_1[16];	  /* default FCB #1 */
    BYTE     pspFCB_2[16];	  /* default FCB #2 */
    IADWORD  rv1D;		  /* reserved */
    BYTE     pspCommandTail[128]; /* command tail (also default DTA) */
} Psp, *PspPtr;

typedef struct {
    IAWORD ofs;
    IAWORD seg;
} EXErelocItem, *EXErelocItemPtr;

#endif
