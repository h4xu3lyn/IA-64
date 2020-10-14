#ifndef _PROGRAM_H
#define _PROGRAM_H

#ifndef XSIM
typedef int Widget;
#define WIDGET_TYPEDEF
#endif

typedef enum { PrgUseCVA, PrgUseTop, PrgUseBot } PrgCmd;

typedef struct {
    BOOL iofsHex;
    unsigned iofsSymWidth;
    BOOL instHex;
    unsigned instSymWidth;
    BOOL cache;
    BOOL useCbit;
    BOOL virtual;
    BOOL useEbit;
    BOOL bigEndian;
    unsigned overlap;
    unsigned columns;
    /* XXX - are these two needed? */
    BOOL oldpswc;
    struct {
	ADDR currVA, prevTopAddr;
	ADDR topAddr, botAddr;
	unsigned nbndl;
	PrgCmd cmd;
	unsigned rows;
	BOOL is;	/* which instruction set */
	BYTE iAmode;	/* which iA execution mode */
	Widget form, hdr, text, gotoST, gotoSL, gotoOT;
    } perProc[NPROC];
    Widget iofsFmt, instFmt;
} prgStruct;

extern prgStruct prgInfo;

#define prgRows		(prgInfo.perProc[cproc].rows)

#define prgBndl		(prgInfo.perProc[cproc].nbndl)

#define prgCmd		(prgInfo.perProc[cproc].cmd)
#define prgColumns	(prgInfo.columns)

#define prgwCVA		(prgInfo.perProc[cproc].currVA)
#define prgwPrevTop	(prgInfo.perProc[cproc].prevTopAddr)

#define prgwTop		(prgInfo.perProc[cproc].topAddr)
#define prgwBot		(prgInfo.perProc[cproc].botAddr)

#define prgwIS		(prgInfo.perProc[cproc].is)
#define prgwIAmode	(prgInfo.perProc[cproc].iAmode)

#define prgOverlap	1

void setPrgwIP(ADDR);
char *prgwLine(ADDR ofs, unsigned *srcrows, unsigned *asmrows);
char *prgwLineIA(ADDR adr, BYTE iAmode, BOOL bp_ip, unsigned *nbytes);

#endif
