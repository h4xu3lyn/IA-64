#include <stdlib.h>
#include <assert.h>
#include <encoder.h>
#include <_decoder.h>
#include "EMInst.h"

#define deposit(val, pos, len) \
    (((unsigned long long)(val) << (64 - (len)) >> (64 - (len) - (pos))))

#define ILL_SEM		8
static unsigned char sem_bits[] = {
/*	  0	   1	    2	     3	      4	       5	6	 7 */
          4, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM,
/*	  8	   9	   10	    11       12	      13       14	15 */
	  5, ILL_SEM, ILL_SEM, ILL_SEM,       6, ILL_SEM, ILL_SEM,       7,
/*	 16	  17	   18	    19       20	      21       22	23 */
    ILL_SEM,       3, ILL_SEM, ILL_SEM,       2, ILL_SEM, ILL_SEM, ILL_SEM,
/*	 24	  25	   26	    27       28	      29       30	31 */
          1, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM, ILL_SEM,
/*	 32 */
          0
};

EncStatus encode_inst(InstID instID, OperandsPtr opnds,
		      EncodedInstPtr inst)
{
    EMDB_info *inst_info;
    EMDB_encode *inst_format;
    unsigned long long bits, op_bits, i = 0, l = 0;
    unsigned int o, mf, adv, f;

    if (instID <= EM_INST_NONE || instID >= EM_INST_LAST)
	return EncBadInstID;

    inst_info = &InstTable[instID];
    inst_format = &EncodingTable[inst_info->format];
    inst->unit = inst_info->unit;
    bits = inst_info->base_encoding;

    if (inst_info->flags & EM_FLAG_TWO_SLOT) {
	inst->extra_bits = 0;
	inst->valid_extra_bits = 1;
    } else
	inst->valid_extra_bits = 0;

    if (inst_info->flags & EM_FLAG_PRED) {
	if (opnds->qp > 63)
	    return EncBadQP;
	bits |= deposit(opnds->qp, EM_PREDICATE_POS, EM_PREDICATE_LEN);
    } else if (opnds->qp)
	return EncBadQP;


    for (f = mf = o = 0; o < MAX_OPERANDS; o++, f += adv) {
#ifdef OPERAND_COUNT
	if (o >= opnds->count)
	    if (inst_info->op[o] == EM_OPTYPE_NONE)
		continue;
	    else
		return EncBadOperand + o;
#endif
	if (!((opnds->u.op[o].type == inst_info->op[o]) ||
	      (opnds->u.op[o].type == OPCLASS(inst_info->op[o]))))
	    return EncBadOperand + o;
	op_bits = opnds->u.op[o].bits;
	adv = 0;
	switch (inst_info->op[o]) {

	case EM_OPTYPE_NONE:
	case EM_OPTYPE_IP:
	case EM_OPTYPE_PREGS_ALL:
	case EM_OPTYPE_PREGS_ROT:
	case EM_OPTYPE_PSR:
	case EM_OPTYPE_PSR_L:
	case EM_OPTYPE_PSR_UM:
	    continue;
	case EM_OPTYPE_IREG_R0:
	    if (op_bits != 0)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_APP_CCV:		/* ar.ccv: not encoded */
	    if (op_bits != 32)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_APP_PFS:		/* ar.pfs: not encoded */
	    if (op_bits != 64)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_APP_CSD:		/* ar.csd: not encoded */
	    if (op_bits != 25)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_ONE:		/* the number 1 - not encoded */
	    if (op_bits != 1)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_EIGHT:		/* the number 8 - not encoded */
	    if (op_bits != 8)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_SIXTEEN:		/* the number 16 - not encoded */
	    if (op_bits != 16)
		return EncBadOperand + o;
	    continue;
	case EM_OPTYPE_IREG:		/* Integer register */
	case EM_OPTYPE_FREG:		/* FP register */
	case EM_OPTYPE_CR:		/* control register */
	case EM_OPTYPE_PMC:		/* indirect register files */
	case EM_OPTYPE_PMD:
	case EM_OPTYPE_PKR:
	case EM_OPTYPE_RR:
	case EM_OPTYPE_IBR:
	case EM_OPTYPE_DBR:
	case EM_OPTYPE_ITR:
	case EM_OPTYPE_DTR:
	case EM_OPTYPE_MSR:
	case EM_OPTYPE_CPUID:
	case EM_OPTYPE_IREG_NUM:	/* ireg number - for chk.a/invala */
	case EM_OPTYPE_FREG_NUM:	/* freg number - for chk.a/invala */
	case EM_OPTYPE_MEM:		/* memory address */
	    if (op_bits > 127)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_IREG_R0_3:	/* r0-r3 */
	    if (op_bits > 3)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_IREG_R1_127:	/* r1-r127 */
	    if (op_bits == 0 || op_bits > 127)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_FREG_F2_127:	/* f2-f127 */
	    if (op_bits < 2 || op_bits > 127)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_BR:		/* branch register */
	    if (op_bits > 7)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_PREG:		/* predicate register */
	case EM_OPTYPE_APP_REG_GRP_LOW:		  /* ARs 0-63 */
	    if (op_bits > 63)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_APP_REG_GRP_HIGH:	/* ARs 64-127 */
	    if (op_bits < 64 || op_bits > 127)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_UIMM:		/* unsigned immediate */
	case EM_OPTYPE_FCLASS:		/* fclass immediate */
	    if (inst_format->op_layout[o].len < 64 &&
		op_bits >> inst_format->op_layout[o].len != 0)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_SIMM:		/* signed immediate */
	case EM_OPTYPE_CMP_UIMM:	/* unsigned immediate of cmp ltu */
	case EM_OPTYPE_CMP4_UIMM:	/* unsigned immediate of cmp4 ltu */

	    break;
	case EM_OPTYPE_SSHIFT_REL:
	    if (op_bits & 0xf)
		return EncBadOperand + o;
	    op_bits = (op_bits - encoderIP()) >> 4;
	    break;
	case EM_OPTYPE_SSHIFT_1:
	    op_bits >>= 1;
	    break;
	case EM_OPTYPE_SSHIFT_16:
	    if (op_bits & 0xffff)
		return EncBadOperand + o;
	    op_bits >>= 16;
	    break;
	case EM_OPTYPE_COUNT_123:
	    op_bits -= 1;
	    if (op_bits > 2)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_COUNT_PACK:
	    if (op_bits == 0);
	    else if (op_bits == 7)
		op_bits = 1;
	    else if (op_bits == 15)
		op_bits = 2;
	    else if (op_bits == 16)
		op_bits = 3;
	    else
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_UDEC:
	    op_bits -= 1;
	    if (inst_format->op_layout[o].len < 64 &&
		op_bits >> inst_format->op_layout[o].len != 0)
		return EncBadOperand + o;
	    break;
	case EM_OPTYPE_CCOUNT:         /* (31 - count) - for pshl */
	    if (op_bits > 31)
		return EncBadOperand + o;
	    op_bits = 31 - op_bits;
	    break;
	case EM_OPTYPE_CPOS:           /* (63 - pos) - for  dep */
	    if (op_bits > 63)
		return EncBadOperand + o;
	    op_bits = 63 - op_bits;
	    break;
	case EM_OPTYPE_SEMAPHORE_INC:
	    if (op_bits + 16u > 32u || sem_bits[op_bits + 16u] == ILL_SEM)
		return EncBadOperand + o;
	    op_bits = sem_bits[op_bits + 16u];
	    break;
	case EM_OPTYPE_ALLOC_IOL:
	    if (op_bits > 96)
		return EncBadOperand + o;
	    switch (o) {
	    case 2:				/* "i" */
		i = op_bits;			/* record it */
		continue;
	    case 3:				/* "l" */
		l = op_bits;			/* record it */
		op_bits = i + l;		/* form sol */
		break;
	    case 4:				/* "o" */
		op_bits = i + l + op_bits;	/* form sof */
		break;
	    }
	    break;
	case EM_OPTYPE_ALLOC_ROT:
	    if (op_bits > 96 || op_bits & 7)
		return EncBadOperand + o;
	    op_bits >>= 3;
	    break;
	case EM_OPTYPE_MUX1:
	    if (!(op_bits == 0 || (op_bits >= 8 && op_bits <= 0xb)))
		return EncBadOperand + o;
	    break;
	default:
#ifdef DEBUG
	    fprintf(stderr, "unknown OPTYPE: %u\n", inst_info->op[o]);
#endif
	    return EncBadOperand + o;
	}

	if (inst_format->op_layout[f].pos != MF) {
	    if (inst_format->op_layout[f].len != 0)
		bits |= deposit(op_bits, inst_format->op_layout[f].pos,
				inst_format->op_layout[f].len);
	} else {
	    unsigned int len, pos, mfi = 0;

	    while ((op_bits != 0) &&
		   ((len = inst_format->fmtArrayptr[mf*FORMAT_SIZE+mfi++])
		    != 0)) {
		pos = inst_format->fmtArrayptr[mf*FORMAT_SIZE+mfi++];
		if (len >= (SLOT_SIZE - MAJOR_OP_SIZE))
		    inst->extra_bits |= deposit(op_bits, pos, len);
		else
		    bits |= deposit(op_bits, pos, len);
		op_bits >>= len;
	    }
	    mf++;
	}
	adv = 1;
    }

    inst->bits = bits;
    return EncOK;
}
