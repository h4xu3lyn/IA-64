#ifndef _DATA_H
#define _DATA_H

#ifndef XSIM
#ifndef WIDGET_TYPEDEF
typedef int Widget;
#endif
#define WINTBLSIZ 20	/* XXX - copied from coreui.h */
#endif

typedef struct {
    BOOL cache;
    BOOL useDbit;
    BOOL virtual;
    BOOL useEbit;
    BOOL bigEndian;
    unsigned overlap;
    unsigned numDataWds;
    unsigned columns;
    char expr[40];
    struct {
	ADDR currVA, lastVA;
	unsigned rows;
	/* XXX - will not work when NPROC > 1 !!! */
	Widget form[WINTBLSIZ], hdr[WINTBLSIZ], text[WINTBLSIZ];
    } perProc[NPROC];
} datStruct;

extern datStruct datInfo;

#define datRows		(datInfo.perProc[cproc].rows)
#define datColumns	(datInfo.columns)
#define datExpr		(datInfo.expr)
#define datwCVA		(datInfo.perProc[cproc].currVA)
#define datwLVA		(datInfo.perProc[cproc].lastVA)
#define datOverlap	1

char *datwLine(ADDR ofs);

#endif
