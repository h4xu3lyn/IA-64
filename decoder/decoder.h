#ifndef _DECODER_H
#define _DECODER_H

#include <instID.h>
#include <operands.h>

#define SLOTS_PER_BUNDLE	3

typedef struct {
    unsigned long long right;
    unsigned long long left;
} Bundle, *BundlePtr;

typedef struct bundle_parts {
    unsigned long long slot[SLOTS_PER_BUNDLE];
    unsigned char templSB;
} BundleParts, *BundlePartsPtr;

typedef struct decoded_instr {
    InstID instID;
    unsigned long long instrBits;
    Operands opnds;
} DecodedInstr, *DecodedInstPtr;

typedef enum { I_Unit, M_Unit, F_Unit, B_Unit, X_Unit, L_Unit, A_Unit,
	       No_Unit } Unit;
typedef enum { SB_Cont, SB_Stop } SB;

typedef struct template_info {
    struct {
	Unit unit;
	SB   stop;
    } slot[SLOTS_PER_BUNDLE];
} TemplateInfo, *TemplateInfoPtr;

TemplateInfoPtr bundle_decode(const BundlePtr bundle,
			      DecodedInstr instrs[SLOTS_PER_BUNDLE],
			      const unsigned int include_opnds);
BundleParts bundle_parts(const BundlePtr bundle);
Bundle bundle_from_parts(const BundlePartsPtr parts);
InstID instr_decode(const Unit unit, const unsigned long long slot,
		    OperandsPtr opnds);
TemplateInfoPtr template_info(const unsigned char templSB);
unsigned char templSB_from_info(const TemplateInfoPtr t);
#ifdef DECODERIP
unsigned long long decoderIP(void);
#endif
#endif
