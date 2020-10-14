#ifndef _PLATFORM_H
#define _PLATFORM_H

/*--------------------------------------------*/
/*  Data structures defined in this file only */
/*--------------------------------------------*/
typedef struct {
    unsigned long long addr;
    unsigned long long data;
    unsigned long long fpnt;
    unsigned int       size;
} IS_t;

/*-------------------------------------------------------*/
/*  Function prototypes core code calls these functions  */
/*-------------------------------------------------------*/
int ioLoad(IS_t *argIn);
int ioStore(IS_t *argIn);

int iomLoad(IS_t *argIn);
int iomStore(IS_t *argIn);

void xtpCycle(BYTE val);

void implArgs(void);
void InitPlatform(void);
void implInit(void);

#endif	/* _SKI_PLATFORM_H */
