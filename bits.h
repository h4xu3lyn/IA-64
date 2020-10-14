#ifndef _BITS_H
#define _BITS_H

#if !BYTE_ORDER || !BIG_ENDIAN || !LITTLE_ENDIAN
# error "Endianness is unknown!"
#endif

#if defined __GNUC__
extern int bad_bitfr (void);
extern int bad_bitfr32 (void);
extern int bad_bitfr8 (void);

# if BYTE_ORDER == BIG_ENDIAN
#define BitfR(i,s,l)	(((union {volatile struct {               \
				unsigned long long  : s; \
				unsigned long long f: l; \
			        } u;                     \
			  } *)(&i + (sizeof(i) != 8 ? bad_bitfr() : 0)))->u.f)
#define BitfR32(i,s,l)	(((union {volatile struct {         \
				unsigned int  : s; \
				unsigned int f: l; \
				} u;               \
			  } *)(&i + (sizeof(i) != 4 ? bad_bitfr32() : 0)))->u.f)
#define BitfR8(i,s,l)	(((union {volatile struct {          \
				unsigned char  : s; \
				unsigned char f: l; \
				} u;                \
			  } *)(&i + (sizeof(i) != 1 ? bad_bitfr8() : 0)))->u.f)
# else /* ! BYTE_ORDER == BIG_ENDIAN */
#define BitfR(i,s,l)	(((union {					       \
				 struct {				       \
					 unsigned long long  : 64-(l)-(s);     \
					 unsigned long long f: l;	       \
				 } u;					       \
			 } *)(&i + (sizeof(i) != 8 ? bad_bitfr () : 0)))->u.f)
#define BitfR32(i,s,l)	(((union {					\
				 struct {				\
					 unsigned int  : 32-(l)-(s);	\
					 unsigned int f: l;		\
				 } u;					\
			 } *)(&i + (sizeof(i) != 4 ? bad_bitfr32 () : 0)))->u.f)
#define BitfR8(i,s,l)	(((union {					\
				 struct {				\
					 unsigned char  : 8-(l)-(s);	\
					 unsigned char f: l;		\
				 } u;					\
			 } *)(&i + (sizeof(i) != 1 ? bad_bitfr8 () : 0)))->u.f)
# endif /* !BYTE_ORDER == BIG_ENDIAN */
#else /* !defined __GNUC__ */
# if BYTE_ORDER == BIG_ENDIAN
#define BitfR(i,s,l)	(((struct { \
				unsigned long long  : s; \
				unsigned long long f: l; \
			   } *)&i)->f)
#define BitfR32(i,s,l)	(((struct { \
				unsigned int  : s; \
				unsigned int f: l; \
			   } *)&i)->f)
#define BitfR8(i,s,l)	(((struct { \
				unsigned char  : s; \
				unsigned char f: l; \
			   } *)&i)->f)
# else /* ! BYTE_ORDER == BIG_ENDIAN */
#define BitfR(i,s,l)	((((struct {					\
				unsigned long long  : 64-(l)-(s);	\
				unsigned long long f: l;		\
			 } *)&i)->f))
#define BitfR32(i,s,l)	((((struct {				\
				unsigned int  : 32-(l)-(s);	\
				unsigned int f: l;		\
			   } *)&i)->f))
#define BitfR8(i,s,l)	((((struct {				\
				unsigned char  : 8-(l)-(s);	\
				unsigned char f: l;		\
			   } *)&i)->f))
# endif /* !BYTE_ORDER == BIG_ENDIAN */
#endif /* !defined __GNUC__ */

#if defined __GNUC__
extern unsigned long long bad_bitfx64 (void);
extern unsigned int       bad_bitfx32 (void);
extern unsigned short     bad_bitfx16 (void);
extern unsigned char      bad_bitfx8 (void);

#define BitfX64(i,s,l) (((unsigned long long)((i) << (s)) >> (64 - (l))) \
		| (sizeof(i) != 8 ? bad_bitfx64 () : 0))
#define BitfX32(i,s,l) (((unsigned int)      ((i) << (s)) >> (32 - (l))) \
		| (sizeof(i) != 4 ? bad_bitfx32 () : 0))
#define BitfX16(i,s,l) (((unsigned short)    ((i) << (s)) >> (16 - (l))) \
		| (sizeof(i) != 2 ? bad_bitfx16 () : 0))
#define BitfX8(i,s,l)  (((unsigned char)     ((i) << (s)) >> ( 8 - (l))) \
		| (sizeof(i) != 1 ? bad_bitfx8  () : 0))

#else /* !defined __GNUC__ */

#define BitfX64(i,s,l) ((unsigned long long)((i) << (s)) >> (64 - (l)))
#define BitfX32(i,s,l) ((unsigned int)      ((i) << (s)) >> (32 - (l)))
#define BitfX16(i,s,l) ((unsigned short)    ((i) << (s)) >> (16 - (l)))
#define BitfX8(i,s,l)  ((unsigned char)     ((i) << (s)) >> ( 8 - (l)))

#endif /* !defined __GNUC__ */

#define BitfX(i,s,l) BitfX64((i),(s),(l))

#endif
