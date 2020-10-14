#ifndef _ASM_H
#define _ASM_H

#include <string.h>
#include <encoder.h>

typedef enum { AsmOK, AsmBadTemplate, AsmBadInst, AsmBadQP, AsmBadOperand,
	       AsmBadOperand1 = AsmBadOperand, AsmBadOperand2,
	       AsmBadOperand3, AsmBadOperand4, AsmBadOperand5,
	       AsmBadOperand6, AsmNoInst, AsmStop, AsmBadEquals, AsmBadAssign
} AsmStatus;

struct asm_id { char *name; InstID id; };
typedef const struct asm_id *AsmIdPtr;

AsmStatus asm_init(void);
AsmStatus asm_inst(const char *str, InstID *instId, OperandsPtr ops,
		   EncodedInstPtr inst);
AsmStatus asm_templ(const char *str, unsigned char *templ);
AsmIdPtr inst_lookup(const char *str);

#endif
