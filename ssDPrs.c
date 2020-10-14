#include <stdarg.h>
#include <string.h>
#include "std.h"
#include "types.h"
#include "exportui.h"
#include "coreui.h"
#include "ssDCmd.h"

#define ARGLEN 4000

extern char *expptr;
extern REG expval;
int yyparse(void);

BOOL evalExpr(const char *expr, unsigned base, REG *retval)
{
    char expstr[ARGLEN+2];

    if (strlen(expr) >= ARGLEN) {
	cmdErr("More than %d characters in expression: %.10s...\n",
	       ARGLEN, expr);
	return NO;
    }
    if (base == DECEXP)
	(void)sprintf(expstr, "! %s", expr);
    else
	(void)sprintf(expstr, "# %s", expr);
    expptr = expstr;
    if (!yyparse()) {
	*retval = expval;
	return YES;
    } else {
	/* XXX - this will fail for long expressions since the cmdErr string
		 can only be 100 total chars */
	cmdErr("Illegal expression: %s\n", expr);
	return NO;
    }
}

/*--------------------------------------------------------------------------
 * catenate$Arguments - concatenate the arguments passed in 'argv' into one
 *  string and return then in the buffer passed.  Begin with argument at
 *  index 'start' and finish with argument at index 'end'.
 *--------------------------------------------------------------------------*/
void catArgs(unsigned start, unsigned end, char *argv[], char *buf)
{
    unsigned i;

    *buf = '\0';
    for (i = start; i <= end; i++) {
	(void)strcat(buf, " ");
	(void)strcat(buf, argv[i]);
    }
#if 0
    cmdWarn("catArgs: string>>%s<<\n", buf);
#endif
}
