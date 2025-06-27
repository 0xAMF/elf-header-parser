#include "../inc/ident_utils.h"
#include "../inc/elfparser.h"

char class_type[3][6] = {"None", "ELF32", "ELF64"};
char data[3][15] = {"Invalid", "Little Endian", "Big Endian"};
char osabi[4][20] = {"UNIX - System V", "HP-UX", "NetBSD", "Linux"};
char elftype[5][5] = {"NONE", "REL", "EXEC", "DYN", "CORE"};


char *get_class_string(elf64_hdr_t *elfheader) {
    return class_type[elfheader->e_ident[EI_CLASS]];
}

char *get_data_string(elf64_hdr_t *elfheader) {
    return data[elfheader->e_ident[EI_DATA]];
}

char *get_osabi_string(elf64_hdr_t *elfheader) {
    return osabi[elfheader->e_ident[EI_OSABI]];
}

char *get_elftype_string(elf64_hdr_t *elfheader) {
    return elftype[elfheader->e_type];

}
