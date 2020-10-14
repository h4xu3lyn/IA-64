#ifndef _SSDCMD_H
#define _SSDCMD_H

#define MAXCMDS	10
#define MAXARGS	64

#define DECEXP	10
#define HEXEXP	16

#ifdef NEW_MP
extern unsigned viewPid;
#else
#define viewPid 0
#endif

#define NPROC   1               /* maximum number of processors */

extern unsigned cproc;              /* current processor number */
extern unsigned nproc;              /* user-specified number of processors */

void cmdOut(const char *name, const char *hdr, const char *buf, FILE *f);

/* ssDCmd.c */
BOOL cmdExLin(char *cmdlin);
BOOL readCmdFile(char *fname);
FILE *cmdOpenFile(char *name, char *mode);
void exitSim(int exitval);

/* ssDPrs.c */
void catArgs(unsigned start, unsigned cnt, char *argv[], char *buf);

/* load.c */
BOOL elfLoad(const char *file_name, int s_argc, char *s_argv[]);

/* menu.c */
BOOL stateRest(unsigned argc, char *argv[]);

#endif
