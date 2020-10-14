#include <string.h>
#include <_decoder.h>

#define sign_ext(i, n)	((((long long)(i) << (64 - (n)))) >> (64 - (n)))

TemplateInfoPtr bundle_decode(const BundlePtr bundle,
			      DecodedInstr instrs[SLOTS_PER_BUNDLE],
			      const unsigned int include_opnds)
{
    TemplateInfoPtr t;
    OperandsPtr s0opnds = 0, s1opnds = 0, s2opnds = 0;
    Bundle swappedBundle;

    swapBundle(swappedBundle, *bundle);

    if (include_opnds) {
	s0opnds = &instrs[0].opnds;
	s1opnds = &instrs[1].opnds;
	s2opnds = &instrs[2].opnds;
    }
    t = &templates[TEMPL_SB(swappedBundle)];
    instrs[0].instID =
	instr_decode(t->slot[0].unit,
		     instrs[0].instrBits = SLOT0(swappedBundle), s0opnds);
    instrs[1].instID =
	instr_decode(t->slot[1].unit,
		     instrs[1].instrBits = SLOT1(swappedBundle), s1opnds);
    instrs[2].instID =
	instr_decode(t->slot[2].unit,
		     instrs[2].instrBits = SLOT2(swappedBundle), s2opnds);
    return t;
}

InstID instr_decode(const Unit unit, const unsigned long long slot,
		    OperandsPtr opnds)
{
    OpDecodePtr op;
    InstID instID;
    unsigned ext, n;

    if (unit < No_Unit) {
	op = &majorOps[unit][MAJOR_OP(slot)];

	while (!INSTR_DECODED(op)) {
	    ext = (slot << op->ext[0].left) >> op->ext[0].right;
	    for (n = 1; (n < NUM_EXTS_PER_LEVEL &&
			 op->ext[n].left != NO_EXTENSION); n++)
		ext = ext << (64 - op->ext[n].right) |
		    (slot << op->ext[n].left) >> op->ext[n].right;

	    op = &opDecodeTable[op->u.opIndex + ext];
	}

	instID = op->u.instID;
    } else
	instID = EM_ILLEGALOP;

    if (opnds) {
	unsigned int o, mf, op_len, s, i2b, sof = 0, sol = 0, adv, f;
	unsigned long long op_bits = 0;
	unsigned long long bits;
	static unsigned long long extra_bits;
	EMDB_info *inst_info = &InstTable[instID];
	EMDB_encode *inst_format = &EncodingTable[inst_info->format];

	if (unit == L_Unit)
	    extra_bits = slot;

	if (inst_info->flags & EM_FLAG_PRED)
	    opnds->qp = extract(slot, EM_PREDICATE_POS, EM_PREDICATE_LEN);
	else
	    opnds->qp = 0;

	opnds->flags = inst_info->flags;
	for (f = mf = o = 0; (o < MAX_OPERANDS); o++, f += adv) {
	    opnds->u.op[o].type = inst_info->op[o];
	    opnds->u.op[o].role =
		(inst_info->op[o] == EM_OPTYPE_NONE) ? EM_OPROLE_NONE :
		(o < inst_info->num_dests) ? EM_OPROLE_DEST : EM_OPROLE_SRC;
		adv = 0;
	    switch (inst_info->op[o]) {
	    case EM_OPTYPE_NONE:
	    case EM_OPTYPE_IP:
	    case EM_OPTYPE_PREGS_ALL:
	    case EM_OPTYPE_PREGS_ROT:
	    case EM_OPTYPE_PSR:
	    case EM_OPTYPE_PSR_L:
	    case EM_OPTYPE_PSR_UM:
	    case EM_OPTYPE_IREG_R0:
		opnds->u.op[o].bits = 0;
		continue;
	    case EM_OPTYPE_APP_CCV:
		opnds->u.op[o].bits = 32;
		continue;
	    case EM_OPTYPE_APP_PFS:
		opnds->u.op[o].bits = 64;
		continue;
	    case EM_OPTYPE_APP_CSD:
		opnds->u.op[o].bits = 25;
		continue;
	    case EM_OPTYPE_ONE:
		opnds->u.op[o].bits = 1;
		continue;
	    case EM_OPTYPE_EIGHT:
		opnds->u.op[o].bits = 8;
		continue;
	    case EM_OPTYPE_SIXTEEN:
		opnds->u.op[o].bits = 16;
		continue;
	    default:
	        break;
	    }
	    op_len = inst_format->op_layout[f].len;
	    if (inst_format->op_layout[f].pos != MF) {
		if (op_len != 0)
		    op_bits = extract(slot, inst_format->op_layout[f].pos,
				      op_len);
	    } else {
		unsigned int len, pos, mfi = 0, total_len = 0;

		op_bits = 0;
		while ((len = inst_format->fmtArrayptr[mf*FORMAT_SIZE+mfi++])
		       != 0) {
		    pos = inst_format->fmtArrayptr[mf*FORMAT_SIZE+mfi++];
		    if (len >= (SLOT_SIZE - MAJOR_OP_SIZE))
			bits = extract(extra_bits, pos, len);
		    else
			bits = extract(slot, pos, len);
		    op_bits |= bits << total_len;
		    total_len += len;
		}
		mf++;
	    }
		adv = 1;
	    switch (inst_info->op[o]) {
	    case EM_OPTYPE_IREG:
	    case EM_OPTYPE_FREG:	/* FP register */
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
	    case EM_OPTYPE_IREG_NUM:
		case EM_OPTYPE_FREG_NUM:
	    case EM_OPTYPE_MEM:
		case EM_OPTYPE_IREG_R0_3:
	    case EM_OPTYPE_BR:		/* branch register */
	    case EM_OPTYPE_PREG:	/* predicate register */
	    case EM_OPTYPE_UIMM:	/* unsigned immediate */
	    case EM_OPTYPE_FCLASS:	/* fclass immediate */
	    case EM_OPTYPE_IMM64:	/* movl immediate */
		break;
	    case EM_OPTYPE_IREG_R1_127:	/* r1-r127 */
		if (op_bits == 0)
		    opnds->flags |= EM_FLAG_GR0_DEST;
		break;
	    case EM_OPTYPE_FREG_F2_127:	/* f2-f127 */
		if (op_bits < 2)
		    opnds->flags |= EM_FLAG_FR0_FR1_DEST;
		break;
	    case EM_OPTYPE_APP_REG_GRP_LOW:	/* ARs 0-63 */
		if (op_bits > 63)
		    opnds->flags |= EM_FLAG_BAD_APP_REG_GRP;
		break;
	    case EM_OPTYPE_APP_REG_GRP_HIGH:	/* ARs 64-127 */
		if (op_bits < 64)
		    opnds->flags |= EM_FLAG_BAD_APP_REG_GRP;
		break;
	    case EM_OPTYPE_SIMM:
	    case EM_OPTYPE_CMP_UIMM:
	    case EM_OPTYPE_CMP4_UIMM:
		op_bits = sign_ext(op_bits, op_len);
		break;
		case EM_OPTYPE_SSHIFT_REL:
#ifdef DECODERIP
		op_bits = decoderIP() + (sign_ext(op_bits, op_len) << 4);
#else
		op_bits = sign_ext(op_bits, op_len) << 4;
#endif
		break;
	    case EM_OPTYPE_SSHIFT_1:
		op_bits = sign_ext(op_bits, op_len) << 1;
		break;
	    case EM_OPTYPE_SSHIFT_16:
		op_bits = sign_ext(op_bits, op_len) << 16;
		break;
	    case EM_OPTYPE_COUNT_123:
		if (++op_bits > 3)
		    opnds->flags |= EM_FLAG_BAD_COUNT;
		break;
	    case EM_OPTYPE_COUNT_PACK:
		op_bits = (op_bits == 0) ? 0 : (op_bits == 1) ? 7 :
		    (op_bits == 2) ? 15 : 16;
		break;
	    case EM_OPTYPE_UDEC:
		op_bits += 1;
		break;
	    case EM_OPTYPE_CCOUNT:
		op_bits = 31 - op_bits;
		break;
	    case EM_OPTYPE_CPOS:
		op_bits = 63 - op_bits;
		break;
	    case EM_OPTYPE_SEMAPHORE_INC:
		s = op_bits >> 2;
		i2b = op_bits & 3;
		op_bits = sign_ext(((s) ? -1 : 1) *
				   ((i2b == 3) ? 1 : 1 << (4 - i2b)), 6);
		break;
	    case EM_OPTYPE_ALLOC_IOL:
		switch (o) {
		case 2:
		    op_bits = 0;
		    adv = 0;
		    break;
		case 3:
		    sol = op_bits;
		    break;
		case 4:
		    sof = op_bits;
		    op_bits = sof - sol;
		    break;
		}
		break;
	    case EM_OPTYPE_ALLOC_ROT:
		op_bits <<= 3;
		if (sof > 96 || op_bits > sof || sol > sof)
		    opnds->flags |= EM_FLAG_BAD_ALLOC;
		break;
	    case EM_OPTYPE_MUX1:
		if (!(op_bits == 0 || (op_bits >= 8 && op_bits <= 0xb)))
		    opnds->flags |= EM_FLAG_BAD_MBTYPE;
		break;
	    default:
#ifdef DEBUG
		fprintf(stderr, "unknown OPTYPE: %u\n", inst_info->op[o]);
#endif
		break;
	    }
	    opnds->u.op[o].bits = op_bits;
	}
    }
    return instID;
}

TemplateInfoPtr template_info(const unsigned char templSB)
{
    if (templSB >= sizeof(templates)/sizeof(templates[0]))
	return 0;
    return &templates[templSB];
}

unsigned char templSB_from_info(const TemplateInfoPtr t)
{
    unsigned char i;

    for (i = 0; i < sizeof(templates)/sizeof(templates[0]); i++)
	if (memcmp(&templates[i], t, sizeof(templates[0])) == 0)
	    break;
    return i;
}