#ifndef _EMINST_H
#define _EMINST_H

#define EM_FLAG_PRED				0x0001
#define EM_FLAG_PRIVILEGED			0x0002
#define EM_FLAG_LMEM				0x0004
#define EM_FLAG_SMEM		       		0x0008
#define EM_FLAG_CHECK_BASE_EQ_DST		0x0010
#define EM_FLAG_FIRST_IN_INSTRUCTION_GROUP	0x0020
#define EM_FLAG_LAST_IN_INSTRUCTION_GROUP	0x0040
#define EM_FLAG_CHECK_SAME_DSTS			0x0080
#define EM_FLAG_SLOT2_ONLY			0x0100
#define EM_FLAG_TWO_SLOT			0x0200
#define EM_FLAG_OK_IN_MLI			0x0400
#define EM_FLAG_CHECK_EVEN_ODD_FREGS		0x0800
#define EM_FLAG_CTYPE_UNC			0x1000

#define EM_FLAG_GR0_DEST			0x80000000
#define EM_FLAG_FR0_FR1_DEST			0x40000000
#define EM_FLAG_BAD_APP_REG_GRP			0x20000000
#define EM_FLAG_BAD_COUNT			0x10000000
#define EM_FLAG_BAD_ALLOC			0x08000000
#define EM_FLAG_BAD_MBTYPE			0x04000000

#define ArchRev0				0x0
#define ArchRev1				0x1
#define Impl_Ipref				0x100
#define Impl_Brl				0x200
#define Impl_Ifetch				0x400
#define Impl_AtomicOps				0x800
#define Impl_VM					0x10000

#include <EMformats.h>
#include <decoder.h>
#include <operands.h>

typedef unsigned long long UInt64;
typedef char Major_opcode;

#define OPCLASS(op)		((op) & ~0x1f)

typedef struct EMDB_info_s {
	Unit		unit;
	Operand_type	op[MAX_OPERANDS];
	unsigned char	num_dests;
	Flags		flags;
	Flags		impl;
	Format		format;
	UInt64		base_encoding;
} EMDB_info;

#define MF 255

#define FORMAT_SIZE     16

extern EMDB_info InstTable[];
extern char formatptr[][FORMAT_SIZE];

typedef struct {
	unsigned char pos;
	unsigned char len;
} layout;

typedef struct EMDB_encode_s {
	layout op_layout[MAX_OPERANDS];
	char *genLayoutStr;
	char *fmtArrayptr;
} EMDB_encode;

extern EMDB_encode EncodingTable[];

#define EM_PREDICATE_POS	0
#define EM_PREDICATE_LEN	6

#endif
