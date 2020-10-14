#ifndef _IA_TYPES_H
#define _IA_TYPES_H

#define IA16	2
#define IA32	4

#define AL_REG	0
#define CL_REG	1
#define DL_REG	2
#define BL_REG	3
#define AH_REG	4
#define CH_REG	5
#define DH_REG	6
#define BH_REG	7

#define AX_REG	0
#define CX_REG	1
#define DX_REG	2
#define BX_REG	3
#define SP_REG	4
#define BP_REG	5
#define SI_REG	6
#define DI_REG	7

#define EAX_REG	0
#define ECX_REG	1
#define EDX_REG	2
#define EBX_REG	3
#define ESP_REG	4
#define EBP_REG	5
#define ESI_REG	6
#define EDI_REG	7

#define ES_REG	0
#define CS_REG	1
#define SS_REG	2
#define DS_REG	3
#define FS_REG	4
#define GS_REG	5

#define NO_REG  8

#define JO_COND		0x0
#define JNO_COND	0x1
#define JB_COND		0x2
#define JNB_COND	0x3
#define JZ_COND		0x4
#define JNZ_COND	0x5
#define JBE_COND	0x6
#define JNBE_COND	0x7
#define JS_COND		0x8
#define JNS_COND	0x9
#define JP_COND		0xA
#define JNP_COND	0xB
#define JL_COND		0xC
#define JNL_COND	0xD
#define JLE_COND	0xE
#define JNLE_COND	0xF
#define JCXZ_COND	0x10

#define LOOPNZ_COND	0x0
#define LOOPZ_COND	0x1
#define LOOP_COND	0x2

#define DISP16_RM	6
#define DISP32_RM	5
#define SIB_RM		4

typedef unsigned long long	IAQWORD;

typedef signed char		IASBYTE;
typedef short			IASWORD;
typedef int			IASDWORD;
typedef long long		IASQWORD;

typedef unsigned short		ADDR2;
typedef unsigned		ADDR4;

#if !BYTE_ORDER || !BIG_ENDIAN || !LITTLE_ENDIAN
# error "Endianness is unknown!"
#endif

typedef struct {
#if BYTE_ORDER == BIG_ENDIAN
    unsigned char mod:2;
    unsigned char reg_op:3;
    unsigned char rm:3;
#else /* BYTE_ORDER == LITTLE_ENDIAN */
    unsigned char rm:3;
    unsigned char reg_op:3;
    unsigned char mod:2;
#endif /* BYTE_ORDER == LITTLE_ENDIAN */
} ModRM;

typedef struct {
#if BYTE_ORDER == BIG_ENDIAN
    unsigned char ss:2;
    unsigned char index:3;
    unsigned char base:3;
#else /* BYTE_ORDER == LITTLE_ENDIAN */
    unsigned char base:3;
    unsigned char index:3;
    unsigned char ss:2;
#endif /* BYTE_ORDER == LITTLE_ENDIAN */
} SIB;

#define NOLOCK	0
#define LOCK	1

#define NOREP	0
#define REP	1
#define REPE	2
#define REPNE	3

typedef struct {
#if BYTE_ORDER == BIG_ENDIAN
    unsigned char op0F:1;
    unsigned char lock:1;
    unsigned char rep:2;
#else /* BYTE_ORDER == LITTLE_ENDIAN */
    unsigned char rep:2;
    unsigned char lock:1;
    unsigned char op0F:1;
#endif /* BYTE_ORDER == LITTLE_ENDIAN */
} LockRep;	/* XXX - rename this */

struct ia_instinfo;

/* read function */
typedef Status	(*PIARF)(struct ia_instinfo *, Accesstype, IADWORD *, ADDR *,
			 ADDR *);
/* write function */
typedef void	(*PIAWF)(struct ia_instinfo *, IADWORD, ADDR, ADDR);
/* execute function */
typedef Status	(*PIAEF)(struct ia_instinfo *);
/* disassembly function */
typedef void	(*PIADASF)(struct ia_instinfo *, char *);

typedef struct ia_instinfo {
    IADWORD imm32;
    IADWORD disp32;
    PIAEF   execFn;
    PIARF   srcRdFn;
    PIARF   destRdFn;
    PIAWF   destWrFn;
    PIADASF dasFn;
    ModRM   modrm;	/* original ModR/M byte for disassembly */
    BYTE    reg;	/* reg/opcode field of ModR/M byte or opcode byte */
    BYTE    scale;	/* scale value of SIB byte (1, 2, 4, or 8) */
    BYTE    index;	/* index value of SIB byte */
    BYTE    base;	/* base field of SIB or R/M field of ModR/M (mod 3) */
    BYTE    cond_seg;	/* Jcc, SETcc, CMOVcc or LOOP condition/seg target */
    BYTE    delta;	/* IP offset to next instruction */
    LockRep lock_rep;	/* lock & rep overrides */
    BYTE    segment;	/* segment reg ID - including overrides, if any */
    BYTE    opSize;	/* operand size - including overrides, if any */
    BYTE    addrSize;	/* address size - including overrides, if any */
    BYTE    mode;	/* IA16/IA32 mode in effect when instr was decoded */
} IAinstInfo, *IAinstInfoPtr;

typedef struct {
    BYTE base;			/* base register */
    BYTE index;			/* index register */
    BYTE defSeg;		/* default segment */
    char *fmt;			/* disassembly format string */
} EaInfo, *EaInfoPtr;

#endif
