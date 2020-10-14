
#ifndef _LIBSRS_H
#define _LIBSRS_H

typedef enum { ERROR, FOUND, NOT_FOUND } RstStat;

BOOL srs_saveState(char *fname);
BOOL srs_restoreState(char *fname);


/* Utility functions */

BOOL srs_nextRstVal(FILE *f, const char *format, ...);
char *srs_errmsgGet(void);
void srs_errmsgSet(const char *fmt, ...);

BOOL saveProcImpl(FILE *f, unsigned cproc);
BOOL saveSysImpl(FILE *f);
BOOL saveSimState(FILE *f);


/* Functions for restoring state */

RstStat restoreProcImpl(FILE *f, char *name, unsigned cproc);
RstStat restoreSysImpl(FILE *f, char *name);
RstStat restoreSimState(FILE *f, char *name);

#endif
