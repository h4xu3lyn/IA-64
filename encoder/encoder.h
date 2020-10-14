#ifndef _ENCODER_H
#define _ENCODER_H

typedef enum { EncOK, EncBadTemplate, EncBadInstID, EncBadQP, EncBadOperand,
	       EncBadOperand1 = EncBadOperand, EncBadOperand2,
	       EncBadOperand3, EncBadOperand4, EncBadOperand5,
	       EncBadOperand6
} EncStatus;

#include <instID.h>
#include <decoder.h>
#include <operands.h>

typedef struct encoded_inst {
    unsigned long long bits;
    unsigned long long extra_bits;
    Unit unit;
    SB	 stop;
    unsigned char valid_extra_bits;
    unsigned char slot;
} EncodedInst, *EncodedInstPtr;

EncStatus encode_inst(InstID instID, OperandsPtr opnds,
		      EncodedInstPtr inst);
unsigned long long encoderIP(void);
char *instFormatName(InstID instID);

#endif
