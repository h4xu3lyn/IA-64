#ifndef _PACKAGE_H
#define _PACKAGE_H


/**************************************************************************
 * File package constants
 **************************************************************************/

/* Defines for magic numbers */
#define SKI_PACKAGE_MAGIC	0xf4841436	/* magic_number */
#define SKI_PACKAGE_MAGIC_SP	0xf4841445	/* previous magic_number */
	/* SP: Small Package.  Kept for compatibility (6/99) */

/* Defines for type */
#define TRACE_PACKAGE	0x10000		/* trace records */
#define ELF_PACKAGE	0x20000		/* an elf package */
#define STATE_PACKAGE	0x30000		/* processor & system state */


/**************************************************************************
 * Auxiliary structs
 **************************************************************************/

typedef struct {
    unsigned short  version;		/* major version number */
    unsigned short  revision;		/* minor revision number */
} Package_Type;


/**************************************************************************
 * File package struct
 **************************************************************************/

typedef struct {
    unsigned		magic_number;	/* Marks as Ski Trace Package */
    Package_Type	type;		/* The type of package */
    unsigned long long	total_length;	/* Package length in bytes */
} Package_Header;

#if 0
/* Package_Header for SKI_PACKAGE_MAGIC_SP */
typedef struct {
    unsigned magic_number;	/* Marks as Ski Trace Package */
    Package_Type type;		/* The type of package */
    unsigned total_length;	/* Package length in bytes */
    unsigned reserved;		/* Reserved, should be 0 */
} Package_Header;
#endif

#endif
