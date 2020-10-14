#ifndef _COREUI_H
#define _COREUI_H


#define EXPRSIZ		20
#define TITLESIZ	80
#define WINTBLSIZ	20
#define NAMLEN		32  

#define RFT "016llx"

typedef enum { ASM, MIXED, SRC } PrgwMode;
typedef enum { BATCH = 0, X_INTERFACE, CURSES_INTERFACE, GTK_INTERFACE } Interface;
typedef REG (*PGetFn)();
typedef BOOL (*PSetFn)();

struct isym {
    char name[NAMLEN];          /* internal symbol name */
    Symtyp type;                /* internal symbol type */
    PGetFn getFn;
    PSetFn setFn;
    void *pval;
    BOOL readonly;		/* is symbol read-only */
    unsigned len;		/* subfield length (len == 0 => not a subfld) */
    unsigned start;		/* subfield start bit position */
    unsigned ndx;		/* index in register set */
    REG align;			/* data item alignment */
    int dbase;			/* default base (hex or dec) */
};

void isymInit(void);
struct isym *isymVLkp(const char *sname);


/*--------------------------------------------------------------------------
 *  Command interface
 *-------------------------------------------------------------------------*/

#define KEYWDSIZ	20
#define DESCRSIZ	200

typedef struct {
    char keywd[KEYWDSIZ];	/* menu lookup keyword */
    unsigned minargs, maxargs;	/* min and max number of arguments */
    char descrip[DESCRSIZ];	/* description (used in help) */
    PFV  fcn;			/* dispatch function */
    char format[DESCRSIZ];	/* command usage (used in help) */
} MENU;

void menuInit(void);
MENU *menuLkp(char *s);

typedef struct {
    char tag[EXPRSIZ];		/* register window tag */
    char title[TITLESIZ];	/* register window title */
    PLF  fcn;			/* line display function */
    unsigned curln;		/* current line */
    char size[EXPRSIZ];		/* register window size.  It is a string to
				   allow use of evalExpr() for GR display */
    BOOL show;			/* show the register set in GUI */
} Regw;

extern Regw regwtbl[], *actRegw;
extern unsigned topregw;

BOOL regwFwdCur(unsigned argc, char *argv[]);
BOOL regwBkwdCur(unsigned argc, char *argv[]);
void regwDrawX(void);
void regwUpdate(void);
void regwUpdateCur(void);
void regwUpdateX(void);
void regwUpdateGtk(void);

typedef struct {
    char tag[EXPRSIZ];		/* data window tag */
    char title[TITLESIZ];	/* data window title */
    unsigned size;		/* data window size */
    PBF  bdfcn;			/* buffer display function */
    BOOL show;			/* show data window in GUI */
} Datw;

extern Datw datwtbl[], *actDatw;
extern unsigned topdatw;

char *dmembuf(unsigned datwSz);
void datwDraw(void);
void datwDrawCur(void);
void datwDrawX(void);
void datwDrawGtk(void);
void datwUpdate(void);
void datwUpdateCur(void);
void datwUpdateX(void);
void datwUpdateGtk(void);
void prgwDraw(void);
void prgwDrawCur(void);
void prgwDrawX(void);
void prgwDrawGtk(void);
void prgwUpdate(void);
void prgwUpdateCur(void);
void prgwUpdateX(void);
void prgwUpdateGtk(void);
void prgwPCRedraw(void);

extern Interface interface;

void cmdErr(const char *, ...);
void cmdWarn(const char *, ...);
void cmdwUpdateCur(void);
void cmdwUpdateX(void);
void cmdwUpdateGtk(void);
void cmdwSetStatus(const char *);
void cmdwSetStatusCur(const char *);
void cmdwSetStatusX(const char *);
void cmdwSetStatusGtk(const char *);
void cmdwPrint(const char *, ...);
void cmdwPrintBatch(const char *);
void cmdwPrintCur(const char *);
void cmdwPrintX(const char *);
void cmdwPrintGtk(const char *);
void msgwPrint(const char *, ...);
void msgwPrintX(const char *);
void msgwPrintGtk(const char *);

void cleanup_execLoop(BOOL showIrate);

void stepUntil_setupX(const char *expr);
BOOL stepUntil_loopX(CTR delay, REG val, const char *expr);

void stepIt_setupX(CTR cnt);
void stepIt_setupGtk(CTR cnt);
void runIt_setupX(void);
void runIt_setupGtk(void);
void uiInit(void);
void scrnInit(void);
void scrnInitBatch(void);
void scrnInitCur(void);
void scrnInitX(void);
void scrnInitGtk(void);
void scrnUpdate(void);
void scrnRedrawCur(void);
void scrnRedrawX(void);
void scrnRedrawGtk(void);
void scrnEnd(void);
void scrnEndCur(void);
void scrnEndX(void);
void scrnEndGtk(void);
void cmdOutBatch(const char *hdr, const char *buf);
void cmdOutCur(const char *hdr, const char *buf);
void cmdOutX(const char *name, const char *hdr, const char *buf);
void cmdOutGtk(const char *name, const char *hdr, const char *buf);
void cmdLoop(void);
void cmdLoopBatch(void);
void cmdLoopCur(void);
void cmdLoopX(void);
void cmdLoopGtk(void);
void initDwUnitTbl(int fd);
char *getSrcLines(ADDR ofs, unsigned *count);
char *getSrcName(ADDR ofs);

char *productInfo(void);

#endif
