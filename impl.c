#include "std.h"
#include "types.h"
#include "libsrs.h"

char *getImplStr(void)
{
    return "SDM 2.1";
}

/*
 * Save/Restore Routines
 */

BOOL saveProcImpl(FILE *f, unsigned cproc)
{
    fprintf(f, "# No processor implementation-dependent state saved\n");
    return YES;
}

BOOL saveSysImpl(FILE *f)
{
    fprintf(f, "# No system implementation-dependent state saved\n");
    return YES;
}

RstStat restoreProcImpl(FILE *f, char *name, unsigned cproc)
{
    return NOT_FOUND;
}

RstStat restoreSysImpl(FILE *f, char *name)
{
    return NOT_FOUND;
}
