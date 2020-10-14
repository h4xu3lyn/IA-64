#ifndef _EXPORTUI_H
#define _EXPORTUI_H

BOOL evalExpr(const char *expr, unsigned base, REG *retval);

typedef enum {
    SINGLE_SYM,
    REGSET_SYM,
    BITF_SYM,
    RS_BITF_SYM,
    REG_SYM,			/* generic 64-bit data items */
    BYTE_SYM,			/* generic 8-bit data items */
    BOOL_SYM,			/* boolean data items */
    STR_SYM,			/* string data items */
    IP_SYM,			/* IP */
    PSR_SYM,			/* PSR */
    GR_SYM,			/* GRs */
    GRNAT_SYM,			/* GR Nats */
    PR_SYM,			/* PRs */
#if 0
    FR_SYM,			/* FRs */
#endif
    FRMANT_SYM,			/* FR mantissas */
    FREXP_SYM,			/* FR exponents */
    FRSGN_SYM,			/* FR signs */
    RRBGF_SYM,			/* rrbg and rrbf */
    RRBP_SYM			/* rrbp */
} Symtyp;

void isymIns(const char *sname, void *pval, Symtyp type, BOOL ronly, int len,
	     int start, REG align, int dbase);

typedef BOOL	(*PFV)(unsigned argc, char **argv);

extern FILE *cmdFile;	/* handle to the "." (command) file */

BOOL menuIns(const char *keywd, int minargs, int maxargs, const char *descrip,
	     PFV fcn, const char *format);

typedef char *	(*PLF)(unsigned line);

BOOL regwIns(const char *tag, const char *title, PLF fcn, const char *size);

BOOL regwMakeActivew(const char *tag);

typedef char *	(*PBF)(unsigned datwSz);	/* ptr to buffer display fcn */


BOOL datwIns(const char *tag, const char *title, PBF bdfcn);


BOOL datwMakeActivew(const char *tag);

unsigned datwSz(const char *tag);

#define IFACELEN	4
#define ARGSIZ		30

typedef enum {
    ARG_BOOL, ARG_INT4, ARG_INT8, ARG_STRING
} ARG;

BOOL argIns(char *name, void *var, ARG kind, char *iface, char *descr);

extern int lookupOption(char *argname, char *argval);

extern int parseOptions(int argc, char *argv[]);

extern void displayOptions(void);

#endif
