#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#include "std.h"
#include "types.h"
#include "sim.h"
#include "state.h"
#include "simmem.h"
#include "os_support.h"

extern char *sim_root;
extern int sim_root_len;

static SimTime simtime0;

BOOL
setInitialTime(char *datestr)
{
        struct timeval tv;
        struct timezone tz;

        if (datestr == NULL) {
                if (gettimeofday (&tv, &tz))
                        return (NO);

                simtime0.simSec = tv.tv_sec;
                simtime0.simUsec = tv.tv_usec;
                simtime0.simMinuteswest = tz.tz_minuteswest;
                simtime0.simDsttime = tz.tz_dsttime;
        } else
                return (NO);

        return (YES);
}

void
getSimTime(SimTime *st)
{
	st->simUsec = simtime0.simUsec + total_insts/mips;
	st->simSec = simtime0.simSec + st->simUsec/1000000U;
	st->simUsec %= 1000000U;
	st->simMinuteswest = simtime0.simMinuteswest;
	st->simDsttime = simtime0.simDsttime;
}

int
simroot(REG arg, char *path, int creat)
{
	char c, *p;

	p = path;
	memBBRd(arg, &c, 1);
	if (c == '/') {
		strcpy(p, sim_root);
		p += sim_root_len;
	}
	memBBRd(arg, p, 0);
	if (p == path)
		return (0);
	if (access(path, F_OK) != 0)
		memBBRd(arg, path, 0);
	return (0);
}
