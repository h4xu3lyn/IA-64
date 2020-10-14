#ifndef _SIGN_EXT_H
#define _SIGN_EXT_H

#define sign_ext(i,n)    ((((long long)(i) << (64 - (n)))) >> (64 - (n)))
#define sign_ext32(i,n)  ((((long)(i) << (32 - (n)))) >> (32 - (n)))

#endif
