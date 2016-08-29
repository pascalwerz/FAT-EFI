#ifndef _CPU_NAMES_H_
#define _CPU_NAMES_H_

#include <mach/machine.h>


/* returns an UTF-8 string */
char * find_cpu_name(cpu_type_t cputype, cpu_subtype_t subcputype);

#endif /* _CPU_NAMES_H_ */