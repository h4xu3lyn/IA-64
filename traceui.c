#include <fcntl.h>
#include "std.h"
#include "types.h"
#ifndef NEW_MP
#include "state.h"
#endif
#include "ssDCmd.h"
#ifdef NEW_MP
BOOL traceOutInit(char *trfile, char *mode, double virtcycle, char *toolname);
#else
#include "libtrace.h"
#endif
#include "libui.h"
#include "exportui.h"
#include "coreui.h"
#include "libcore.h"

BOOL archTraceInit(FILE *trcf, char errmsg[]);

BOOL traceGen(unsigned argc, char *argv[])
{
    REG expr;

    if (!evalExpr(argv[0], HEXEXP, &expr))
	return NO;
    if (!setTraceEnb(!!expr)) {
	cmdWarn("No trace file specified yet\n");
	return NO;
    }
    return YES;
}

BOOL traceFile(unsigned argc, char *argv[])
{
    static char tmode[] = { '\0' };
    CTR ti = getTotalInsts();

    if (argc > 1) {
	tmode[0] = argv[1][0];
	if (argv[1][1] || (tmode[0] != 'w' && tmode[0] != 'a')) {
	    cmdErr("Illegal output file specification: %s\n", argv[1]);
	    return NO;
	}
    } else
	tmode[0] = 'w';
    if (!traceOutInit(argv[0], tmode, ti, getSimID()))
	return NO;
    initTraceVcy();
    initTraceFlags();
    return YES;
}

