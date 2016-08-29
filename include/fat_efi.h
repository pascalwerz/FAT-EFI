//
//  fatefi.h
//  
//
//  Created by Pascal on 17/08/2016.
//
//

#ifndef fatefi_h
#define fatefi_h

/*
 * This header file describes the structures of the file format for "FAT EFI"
 * architecture specific file (wrapper design).  At the begining of the file
 * there is one fat_header structure followed by a number of fat_arch
 * structures.  For each architecture in the file, specified by a pair of
 * cputype and cpusubtype, the fat_header describes the file offset, file
 * size and alignment in the file of the architecture specific member.
 *
 * All structures defined here are always written and read to/from disk
 * in little-endian order.
 */

/*
 * <mach/machine.h> is needed here for the cpu_type_t and cpu_subtype_t types
 * and contains the constants for the possible values of these types.
 */
#include <stdint.h>
#include <mach/machine.h>

#define FATEFI_MAGIC    0x0ef1fab9
#define FATEFI_CIGAM    0xb9faf10e  /* NXSwapLong(FATEFI_MAGIC) */

// same as fat structure
struct fatefi_header {
    uint32_t	magic;		/* FATEFI_MAGIC */
    uint32_t	nfat_arch;	/* number of structs that follow */
};

// same as fat structure
struct fatefi_arch {
    cpu_type_t	cputype;	/* cpu specifier (int) */
    cpu_subtype_t	cpusubtype;	/* machine specifier (int) */
    uint32_t	offset;		/* file offset to this object file */
    uint32_t	size;		/* size of this object file */
    uint32_t	align;		/* alignment as a power of 2 */
};


#endif /* fatefi_h */
