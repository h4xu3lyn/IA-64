#ifndef _STD_H
#define _STD_H

#if defined HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdlib.h>
#include <stdio.h>

typedef enum {NO, YES}	BOOL;

#define BEL		'\a'

#if HAVE_STRTOULL
extern unsigned long long strtoull(const char *, char **, int);
#else /* ! HAVE_STRTOULL */
# if HAVE___STRTOULL
extern unsigned long long __strtoull(const char *, char **, int);
#   define strtoull __strtoull
# else /* ! HAVE___STRTOULL */
#   error "You do not have strtoull!"
# endif /* ! HAVE___STRTOULL */
#endif /* ! HAVE_STRTOULL */

/* What is the host endiannes? */
#if defined ENDIANESS_IN_SYS_PARAM_H
# include <sys/types.h>
# include <sys/param.h>
#else /* !defined ENDIANESS_IN_SYS_PARAM_H */
# if !defined HAVE_CONFIG_H
#   warning "Assuming BIG_ENDIAN"
/* In case we do not have config.h assume BIG_ENDIAN */
#   define BIG_ENDIAN 4321
#   define LITTLE_ENDIAN 1234
#   define BYTE_ORDER BIG_ENDIAN
# else
#  define BIG_ENDIAN 4321
#  define LITTLE_ENDIAN 1234
#  ifdef WORDS_BIGENDIAN
#   define BYTE_ORDER BIG_ENDIAN
#  else
#   define BYTE_ORDER LITTLE_ENDIAN
#  endif
# endif 
#endif

#endif
