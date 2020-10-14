#include "std.h"
#include "types.h"
#include "ia64.h"
#include "ssDCmd.h"
#include "libcore.h"
#define NPROC 1
#define cproc 0
#include "data.h"

BOOL bstats = NO;

void runIt(BOOL);

#ifdef TO_BE_USED
tlbBatch()
{
}
#endif

void scrnInitBatch(void)
{
    datInfo.numDataWds = 4;
}

void cmdwPrintBatch(const char *s)
{
    (void)fputs(s, stderr);
}

void cmdOutBatch(const char *hdr, const char *buf)
{
    (void)fputs(hdr, stderr);
    (void)fputs(buf, stderr);
}

void cmdLoopBatch(void)
{
    if (fileLoaded && !getExited())
	runIt(bstats);
    else
	(void)fprintf(stderr, "Nothing to run\n");
    exitSim(grGet(0, 8));
}
