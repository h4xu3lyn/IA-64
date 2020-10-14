#include <string.h>
#include "std.h"
#include "bits.h"
#include "types.h"
#include "state.h"
#include "sim.h"
#include "libcore.h"
#include "libtrace.h"
#include "trace.h"


unsigned traceEnb = NO;
unsigned traceMode = NO;
FILE *tracef = NULL;

unsigned trc_flags = 1;

Capsule_Trec		capsule_trec	= { CAPSULE_TREC };
Context_Switch_Trec	cswitch_trec	= { CONTEXT_SWITCH_TREC };
Interruption_Trec	irpt_trec	= { INTERRUPTION_TREC };
Discontinuity_Trec	disc_trec	= { DISCONTINUITY_TREC };
Virt_Cycle_Trec		vcycle_trec	= { VIRT_CYCLE_TREC };
Ioffset_Trec		ioffset_trec	= { IOFFSET_TREC };
Bundle_Trec		bundle_trec	= { BUNDLE_TREC };
Branch_Trec		branch_trec	= { BRANCH_TREC,
					    BR_TRC_TYPE_UNKNOWN,
					    BR_TRC_HINT_UNKNOWN,
					    BR_TRC_BREG_UNKNOWN };
Doffset_Trec		doffset_trec	= { DOFFSET_TREC,
					    DOFF_TRC_TY_UNKNOWN,
					    DOFF_TRC_SZ_UNKNOWN };
Region_Chng_Trec	region_trec	= { REGION_CHNG_TREC };
Prev_Pfs_Trec		prev_pfs_trec	= { PREV_PFS_TREC };
Br_Pred_Trec		br_pred_trec	= { BRPRED_TREC };
Ar_Tgt_Trec		ar_tgt_trec	= { ARTGT_TREC };

static CTR traceVcy;

void tracePrevPFS(REG prevPfs)
{
    if (traceEnb)
	WRT_PREV_PFS_TR(prevPfs);
}

void traceBrPred(REG br)
{
    if (traceEnb)
	WRT_BRPRED_TR(br);
}

void traceArTgt(REG ar)
{
    if (traceEnb)
	WRT_ARTGT_TR(ar);
}

BOOL setTraceEnb(BOOL enb)
{
    if (enb) {
	if (!tracef)
	    return NO;
	preInst |= PRE_TRACE;
	traceEnb = YES;
    } else {
	preInst &= ~PRE_TRACE;
	traceEnb = NO;
	traceFlush(tracef);
    }
    return YES;
}

void initTraceVcy(void)
{
    traceVcy = total_insts;
}

void initTraceFlags(void)
{
    FIRST_TREC = 1;
}

void traceDisc(void)
{
    if (traceEnb && total_insts - traceVcy > 1) {
	WRT_DISC_TR();
	WRT_VCYCLE_TR();
    }
}

void traceVcyEnb(void)
{
    if (traceEnb)
	traceVcy = total_insts;
}

