#ifndef __DECODER_H
#define __DECODER_H

#include <decoder.h>
#include <EMInst.h>

#define extract(slot, pos, len) \
    ((slot) << (64 - ((pos) + (len))) >> (64 - (len)))

#define NO_EXTENSION	64
#define NUM_EXTS_PER_LEVEL	3
#define INSTR_DECODED(op)	((op)->ext[0].left == NO_EXTENSION)

#define BUNDLE_SIZE		128
#define SLOT_SIZE		41
#define SLOT_MASK		((1ull << SLOT_SIZE) - 1)
#define TEMPL_SB_SIZE		(BUNDLE_SIZE - (SLOTS_PER_BUNDLE * SLOT_SIZE))
#define TEMPL_SB_MASK		((1ull << TEMPL_SB_SIZE) - 1)
#define MAJOR_OP_SIZE		4
#define MAJOR_OP(slot)		extract(slot, SLOT_SIZE-MAJOR_OP_SIZE, \
					MAJOR_OP_SIZE)
#define NUM_UNITS		6
#define NUM_TEMPL_SBS		(1 << TEMPL_SB_SIZE)
#define NUM_MAJOR_OPS		(1 << MAJOR_OP_SIZE)
#define SLOT1L_SIZE	(BUNDLE_SIZE/2-SLOT_SIZE)
#define SLOT1L_MASK	((1ull << SLOT1L_SIZE) - 1)
#define SLOT1R_SIZE	(BUNDLE_SIZE/2-(SLOT_SIZE+TEMPL_SB_SIZE))
#define SLOT1R_MASK	((1ull << SLOT1R_SIZE) - 1)
#define SLOT1(b)	((SLOT1L(b) << SLOT1R_SIZE) | SLOT1R(b))
#define SLOT2(b)	extract((b).left, SLOT1L_SIZE, SLOT_SIZE)
#define SLOT1L(b)	extract((b).left, 0, SLOT1L_SIZE)
#define SLOT1R(b)	extract((b).right, SLOT_SIZE+TEMPL_SB_SIZE, SLOT1R_SIZE)
#define SLOT0(b)	extract((b).right, TEMPL_SB_SIZE, SLOT_SIZE)
#define TEMPL_SB(b)	((b).right & TEMPL_SB_MASK)
#define BUNDLE_RIGHT(templ_sb, slot0, slot1) \
	(((templ_sb) & TEMPL_SB_MASK) | \
	 (((slot0) & SLOT_MASK) << TEMPL_SB_SIZE) | \
	 (((slot1) & SLOT1R_MASK) << (TEMPL_SB_SIZE+SLOT_SIZE)))
#define BUNDLE_LEFT(slot1, slot2) \
	((((slot1) >> SLOT1R_SIZE) & SLOT1L_MASK) | \
	 (((slot2) & SLOT_MASK) << SLOT1L_SIZE))


typedef struct {
    unsigned char left;
    unsigned char right;
} Ext, *ExtPtr;

typedef struct op_decode {
    union {
	unsigned short opIndex;
	InstID instID : 16;
    } u;
    Ext ext[NUM_EXTS_PER_LEVEL];
} OpDecode, *OpDecodePtr;

extern OpDecode majorOps[NUM_UNITS][NUM_MAJOR_OPS];
extern OpDecode opDecodeTable[];
extern TemplateInfo templates[NUM_TEMPL_SBS];

#ifdef INLINE
#include <machine/inline.h>
#endif

# include "std.h"

#if !BYTE_ORDER || !BIG_ENDIAN || !LITTLE_ENDIAN
# error "Endianness is unknown!"
#endif

#if BYTE_ORDER == LITTLE_ENDIAN
#define swapBundle(tgt, src)	((tgt) = (src))
#else
#if defined(INLINE) && defined(__IA64__)
#define swapBundle(tgt, src) \
    (tgt).left  = _Asm_mux1(_MBTYPE_REV, (src).left); \
    (tgt).right = _Asm_mux1(_MBTYPE_REV, (src).right);
#elif defined(INLINE) && defined(_PA_RISC2_0)
#define swapBundle(tgt, src) \
{ \
    register unsigned long long swappedLeft, swappedRight, \
	bundleLeft, bundleRight; \
 \
    bundleLeft =  (src).left; \
    bundleRight = (src).right; \
    (void)_asm("PERMH,3210", bundleLeft, bundleLeft); \
    (void)_asm("PERMH,3210", bundleRight, bundleRight); \
    (void)_asm("HSHL", bundleLeft, 8, swappedLeft); \
    (void)_asm("HSHR,U", bundleLeft, 8, bundleLeft); \
    (void)_asm("HSHL", bundleRight, 8, swappedRight); \
    (void)_asm("HSHR,U", bundleRight, 8, bundleRight); \
    (void)_asm("OR", bundleLeft, swappedLeft, swappedLeft); \
    (void)_asm("OR", bundleRight, swappedRight, swappedRight); \
    (tgt).left  = swappedLeft; \
    (tgt).right = swappedRight; \
}
#elif defined(INLINE) && (defined(_PA_RISC1_1) || defined(_PA_RISC1_0))
#define swapBundle(tgt, src) \
{ \
    register unsigned word0, word1, word2, word3, tmp0, tmp1, tmp2, tmp3, \
	*swp = (unsigned *)&(src), *twp = (unsigned *)&(tgt); \
 \
    word0 = *(swp); \
    word1 = *(swp + 1); \
    (void)_asm("SHD", word0, word0, 16, tmp0); \
    (void)_asm("DEP", tmp0, 15, 8, tmp0); \
    (void)_asm("SHD", word0, tmp0, 8, tmp0); \
    *(twp + 1) = tmp0; \
    (void)_asm("SHD", word1, word1, 16, tmp1); \
    word2 = *(swp + 2); \
    (void)_asm("DEP", tmp1, 15, 8, tmp1); \
    word3 = *(swp + 3); \
    (void)_asm("SHD", word1, tmp1, 8, tmp1); \
    *(twp) = tmp1; \
    (void)_asm("SHD", word2, word2, 16, tmp2); \
    (void)_asm("DEP", tmp2, 15, 8, tmp2); \
    (void)_asm("SHD", word2, tmp2, 8, tmp2); \
    *(twp + 3) = tmp2; \
    (void)_asm("SHD", word3, word3, 16, tmp3); \
    (void)_asm("DEP", tmp3, 15, 8, tmp3); \
    (void)_asm("SHD", word3, tmp3, 8, tmp3); \
    *(twp + 2) = tmp3; \
}
#else
#define swapBundle(tgt, src) \
    (tgt).left = \
	(((src).left & 0xff00000000000000ull) >> 56) | \
	(((src).left & 0x00ff000000000000ull) >> 40) | \
	(((src).left & 0x0000ff0000000000ull) >> 24) | \
	(((src).left & 0x000000ff00000000ull) >>  8) | \
	(((src).left & 0x00000000ff000000ull) <<  8) | \
	(((src).left & 0x0000000000ff0000ull) << 24) | \
	(((src).left & 0x000000000000ff00ull) << 40) | \
	(((src).left & 0x00000000000000ffull) << 56); \
    (tgt).right = \
	(((src).right & 0xff00000000000000ull) >> 56) | \
	(((src).right & 0x00ff000000000000ull) >> 40) | \
	(((src).right & 0x0000ff0000000000ull) >> 24) | \
	(((src).right & 0x000000ff00000000ull) >>  8) | \
	(((src).right & 0x00000000ff000000ull) <<  8) | \
	(((src).right & 0x0000000000ff0000ull) << 24) | \
	(((src).right & 0x000000000000ff00ull) << 40) | \
	(((src).right & 0x00000000000000ffull) << 56);
#endif
#endif

#endif
