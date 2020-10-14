#ifndef _MACHDEP_H
#define _MACHDEP_H

#define	SKI_NFDS		20

typedef struct {
	ADDR	addr;
	WORD	len;
} SscDiskReq;

typedef struct {
	int	fd;
	WORD	count;
} SscDiskStat;

typedef struct {
	WORD	year;
	WORD	mon;
	WORD	mday;
	WORD	hour;
	WORD	min;
	WORD	sec;
	WORD	msec;
	WORD	wday;
} SscTime;

typedef struct {
	WORD	ssc_Sec;
	WORD	ssc_Usec;
} SscTimeval;

typedef struct {
	WORD	ssc_Minuteswest;
	WORD	ssc_Dsttime;
} SscTimezone;

#endif
