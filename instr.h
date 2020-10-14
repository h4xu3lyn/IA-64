#ifndef _INSTR_H
#define _INSTR_H

typedef BOOL (*PdecFn)(DWORD, INSTINFO *);

typedef struct instr {
    PdecFn pdecFn;
    PCF combFn;
    unsigned int flags;
    ICNTS cnt;
} Instr, *InstrPtr;

extern InstrPtr instrs;

#endif
