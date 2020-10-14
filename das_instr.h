#ifndef _DAS_INSTR_H
#define _DAS_INSTR_H

#define OPINDEX_NONE	-1

typedef struct {
    char *mnem;		/* mnemonic */
    short tgtOp, tagOp;	/* operand index of target/tag, OPINDEX_NONE if none */
    unsigned short pseudo;	/* index of first pseudo op, 0 if none */
} DasInstr, *DasInstrPtr;

extern DasInstrPtr dasInstrs;

#endif
