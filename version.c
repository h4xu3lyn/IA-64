#include "std.h"

#if !defined VERSION
#  define VERSION "1.1.0"
#endif

#if 0
char version[] = "Version " VERSION " [" HOST "]";
#else
char version[] = "Version " VERSION
# ifdef SKI_RELEASE
		     "-" SKI_RELEASE
# endif
		     ;
#endif
