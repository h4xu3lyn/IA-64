#ifndef _OS_SUPPORT_H
#define _OS_SUPPORT_H

typedef struct {
	WORD	simSec;
	WORD	simUsec;
	WORD	simMinuteswest;
	WORD	simDsttime;
} SimTime;

BOOL setInitialTime(char *datestr);
void getSimTime(SimTime *st);

int simroot(REG arg, char *path, int creat);

#endif
