#include "cpu_names.h"
#include <stdio.h>



/* based on mach/machine.h */

typedef struct {
    cpu_type_t cpu;
    cpu_subtype_t subcpu;
    char * name;
} cpu_naming;



/* subcpu shall be ignored in generic_names */
static cpu_naming generic_names[] =
{
    { CPU_TYPE_ANY,       0,    "\"any\" CPU" },
    { CPU_TYPE_VAX,       0,    "VAX" },
    { CPU_TYPE_MC680x0,   0,    "68000" },
    { CPU_TYPE_X86,       0,    "x86 (32 bits)" },
    { CPU_TYPE_X86_64,    0,    "x86 (64 bits)" },
    { CPU_TYPE_MC98000,   0,    "MC98000" },
    { CPU_TYPE_HPPA,      0,    "PA-RISC" },
    { CPU_TYPE_ARM,       0,    "ARM (32 bits)" },
    { CPU_TYPE_ARM64,     0,    "ARM (64 bits)" },
    { CPU_TYPE_MC88000,   0,    "MC88000" },
    { CPU_TYPE_SPARC,     0,    "Sparc" },
    { CPU_TYPE_I860,      0,    "i860" },
    { CPU_TYPE_POWERPC,   0,    "PowerPC (32 bits)" },
    { CPU_TYPE_POWERPC64, 0,    "PowerPC (64 bits)" },
};



/* as mach/machine.h is not much commented, and many CPUs listed are little or not known, these names still needs to be tuned */
static cpu_naming cpu_names[] =
{
    { CPU_TYPE_VAX,       CPU_SUBTYPE_MULTIPLE,       "multiple VAX" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX_ALL,        "generic VAX" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX780,         "VAX 780" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX785,         "VAX 785" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX750,         "VAX 750" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX730,         "VAX 730" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_UVAXI,          "\u00b5Vax I" },	// \u00b5 is the "micro" symbol
    { CPU_TYPE_VAX,       CPU_SUBTYPE_UVAXII,         "\u00b5Vax II" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX8200,        "VAX 8200" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX8500,        "VAX 8500" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX8600,        "VAX 8600" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX8650,        "VAX 8650" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_VAX8800,        "VAX 8800" },
    { CPU_TYPE_VAX,       CPU_SUBTYPE_UVAXIII,        "\u00b5VAX III" },

    { CPU_TYPE_MC680x0,   CPU_SUBTYPE_MULTIPLE,       "multiple MC68000" },
    { CPU_TYPE_MC680x0,   CPU_SUBTYPE_MC680x0_ALL,    "generic MC68000" },
    { CPU_TYPE_MC680x0,   CPU_SUBTYPE_MC68040,        "MC68040" },
    { CPU_TYPE_MC680x0,   CPU_SUBTYPE_MC68030_ONLY,   "MC68030" },

    { CPU_TYPE_X86,       CPU_SUBTYPE_MULTIPLE,       "multiple x86 (32 bits)" },
    { CPU_TYPE_X86,       CPU_SUBTYPE_X86_ALL,        "generic x86 (32 bits)" },
    { CPU_TYPE_X86,       CPU_SUBTYPE_X86_ARCH1,      "i486 (32 bits)" },

    { CPU_TYPE_X86_64,    CPU_SUBTYPE_MULTIPLE,       "multiple x86 (64 bits)" },
    { CPU_TYPE_X86_64,    CPU_SUBTYPE_X86_64_ALL,     "generic x86 (64 bits)" },
    { CPU_TYPE_X86_64,    CPU_SUBTYPE_X86_64_H,       "x86 Haswell (64 bits)" },

    { CPU_TYPE_MC98000,   CPU_SUBTYPE_MULTIPLE,       "multiple MC98000" },
    { CPU_TYPE_MC98000,   CPU_SUBTYPE_MC98000_ALL,    "generic MC98000" },
    { CPU_TYPE_MC98000,   CPU_SUBTYPE_MC98601,        "MC98601" },

    { CPU_TYPE_HPPA,      CPU_SUBTYPE_MULTIPLE,       "multiple PA-RISC" },
    { CPU_TYPE_HPPA,      CPU_SUBTYPE_HPPA_ALL,       "generic PA-RISC" },
    { CPU_TYPE_HPPA,      CPU_SUBTYPE_HPPA_7100,      "PA-7100" },
    { CPU_TYPE_HPPA,      CPU_SUBTYPE_HPPA_7100LC,    "PA-7100LC" },

    { CPU_TYPE_ARM,       CPU_SUBTYPE_MULTIPLE,       "multiple ARM (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_ALL,        "generic ARM (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V4T,        "ARM v4T (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V6,         "ARM v6 (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V5TEJ,      "ARM v5TEJ (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_XSCALE,     "ARM XScale (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V7,         "ARM v7 (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V7F,        "ARM Cortex A9 (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V7S,        "ARM Swift (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V7K,        "ARM v7K (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V6M,        "ARM v6M (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V7M,        "ARM v7M (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V7EM,       "ARM v7EM (32 bits)" },
    { CPU_TYPE_ARM,       CPU_SUBTYPE_ARM_V8,         "ARM v8 (32 bits)" },
            
    { CPU_TYPE_ARM64,     CPU_SUBTYPE_MULTIPLE,       "multiple ARM (64 bits)" },
    { CPU_TYPE_ARM64,     CPU_SUBTYPE_ARM64_ALL,      "generic ARM (64 bits)" },
    { CPU_TYPE_ARM64,     CPU_SUBTYPE_ARM64_V8,       "ARM v8 (64 bits)" },

    { CPU_TYPE_MC88000,   CPU_SUBTYPE_MULTIPLE,       "multiple MC88000" },
    { CPU_TYPE_MC88000,   CPU_SUBTYPE_MC88000_ALL,    "generic MC88000" },
    { CPU_TYPE_MC88000,   CPU_SUBTYPE_MC88100,        "MC88100" },
    { CPU_TYPE_MC88000,   CPU_SUBTYPE_MC88110,        "MC88110" },

    { CPU_TYPE_SPARC,     CPU_SUBTYPE_MULTIPLE,       "multiple Sparc" },
    { CPU_TYPE_SPARC,     CPU_SUBTYPE_SPARC_ALL,      "generic Sparc" },

    { CPU_TYPE_I860,      CPU_SUBTYPE_MULTIPLE,       "multiple i860" },
    { CPU_TYPE_I860,      CPU_SUBTYPE_I860_ALL,       "generic i860" },
    { CPU_TYPE_I860,      CPU_SUBTYPE_I860_860,       "i860" },

    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_MULTIPLE,       "multiple PowerPC (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_ALL,    "generic PowerPC (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_601,    "PowerPC 601 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_602,    "PowerPC 602 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_603,    "PowerPC 603 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_603e,   "PowerPC 603e (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_603ev,  "PowerPC 603ev (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_604,    "PowerPC 604 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_604e,   "PowerPC 604e (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_620,    "PowerPC 620 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_750,    "PowerPC 750 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_7400,   "PowerPC G4 7400 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_7450,   "PowerPC G4 7450 (32 bits)" },
    { CPU_TYPE_POWERPC,   CPU_SUBTYPE_POWERPC_970,    "PowerPC G5 (32 bits)" },

    { CPU_TYPE_POWERPC64, CPU_SUBTYPE_MULTIPLE,       "multiple PowerPC (64 bits)" },
    { CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL,    "generic PowerPC (64 bits)" },
    { CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970,    "PowerPC G5 (64 bits)" },

};



char * find_cpu_name(cpu_type_t cputype, cpu_subtype_t subcputype)
{
static char result[256];
int i;


for (i = 0; i < sizeof(cpu_names)/sizeof(*cpu_names); i++)
	{
	if ((cpu_names[i].cpu == cputype) && (cpu_names[i].subcpu == subcputype))
		return cpu_names[i].name;
	}

for (i = 0; i < sizeof(generic_names)/sizeof(*generic_names); i++)
	{
	if (generic_names[i].cpu == cputype)
		{
		snprintf(result, sizeof(result), "Unknown %s subtype %lld", generic_names[i].name, (long long) subcputype);
		return result;
		}
	}

snprintf(result, sizeof(result), "Unknown cputype %lld, subtype %lld", (long long) cputype, (long long) subcputype);
return result;
}
