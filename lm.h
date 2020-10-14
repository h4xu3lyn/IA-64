#ifndef _LM_H
#define _LM_H

#define MAX_LOAD_MODULES 12

typedef struct {
  char *name;
  ADDR text_base, text_end;
  ADDR unwind_base;
} LMINFO;

extern unsigned numLms;

#endif
