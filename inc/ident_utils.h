#ifndef _IDENT_UTILS_H
#define _IDENT_UTILS_H

#include "elfparser.h"

char *get_class_string(elf64_hdr_t *elfheader);
char *get_data_string(elf64_hdr_t *elfheader);
char *get_osabi_string(elf64_hdr_t *elfheader);
char *get_elftype_string(elf64_hdr_t *elfheader);
char *get_sectype_string(uint32_t type);
char *get_secflag_string(uint64_t type);


#endif // !_IDENT_UTILS_H
