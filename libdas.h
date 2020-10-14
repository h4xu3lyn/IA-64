#ifndef _LIBDAS_H
#define _LIBDAS_H


#ifndef _DECODER_H
typedef struct bundle {
    unsigned long long left, right;
} Bundle;
#endif
#define MAX_DAS_LEN	512

typedef enum {
    DasNoOpts,			/* no options */
    DasTemplate = 0x1,		/* include template type in i0Str */
    DasTemplateComment = 0x3,	/* include template type as comment */
    DasSepStopLines = 0x4,	/* put ";;" (stops) on separate lines */
    DasPseudoOps = 0x8,		/* check for pseudo-ops */
    DasSpaceOperands = 0x10,	/* space-separate operands */
    DasRegNames = 0x20,		/* use register names (gp, sp, rp, ar., etc) */
    DasFormatNumbers = 0x40,	/* include format numbers */
    DasFormatComment = 0xC0,	/* include format number as comment */
    DasTemplateCommas = 0x100,	/* include commas in template types */
    DasHexAddresses = 0x200,	/* include hex addresses */
    DasStackedRegNames = 0x420,	/* use register names (in, loc, out, rot) */
    DasTemplateLC = 0x800,	/* lower case template type */
    DasNoSymMovlImm = 0x1000,	/* movl immediates not symbolic */
    DasNoMnemonicPad = 0x2000	/* mnemonic not padded to 16 spaces */
} DasOptions;

typedef struct {
    char *name;
    unsigned int type;
    long long addend;
} DasRelocation, *DasRelocationPtr;

#define dasBundle(bndl, i0Str, i1Str, i2Str) \
		dasBundleSBT(bndl, i0Str, i1Str, i2Str, 0, 0)
#define dasBundleSB(bndl, i0Str, i1Str, i2Str, sb) \
		dasBundleSBT(bndl, i0Str, i1Str, i2Str, sb, 0)

void dasInit(DasOptions opts, int width);
void dasBundleSBT(Bundle *bndl, char *i0Str, char *i1Str, char *i2Str,
		 SB sb[SLOTS_PER_BUNDLE], char *tStr);
char *hexBundle(Bundle *bndl, char *str);
char *dasInst(Unit unit, unsigned long long instBits,
	      unsigned long long extraInstBits, char *iStr);
char *dasEncodedInst(struct encoded_inst *inst, char *iStr);
unsigned int bundleTargets(Bundle *bndl, unsigned long long tgtAdr[]);
unsigned int dasRelocation(unsigned long long addr, DasRelocationPtr reloc);
void dasSetFrameSize(unsigned int ins, unsigned int locs, unsigned int outs,
		     unsigned int rots);

#endif
