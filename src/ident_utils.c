#include "../inc/ident_utils.h"
#include "../inc/elfparser.h"
#include <stdint.h>
#include <stdio.h>

char class_type[3][6] = {"None", "ELF32", "ELF64"};
char data[3][15] = {"Invalid", "Little Endian", "Big Endian"};
char osabi[4][20] = {"UNIX - System V", "HP-UX", "NetBSD", "Linux"};
char elftype[5][5] = {"NONE", "REL", "EXEC", "DYN", "CORE"};
char sectype[12][10] = {"NULL", "PROGBITS", "SYMTAB", "STRTAB",
                        "RELA", "HASH", "DYNAMIC", "NOTE", "NOBITS",
                        "REL", "SHLIB", "DYNSIM"};
char sectypestr[20];
char secflagstr[4] = " ";

#define SHF_WRITE     0x01
#define SHF_ALLOC     0x02
#define SHF_EXECINSTR 0x04
#define SHF_INFO_LINK 0x40


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

char *get_sectype_string(uint32_t type) {
    if (type < 0 || type > 11) {
        sprintf(sectypestr, "0x%05X", type);
        return sectypestr;
    }
    return sectype[type];
}

char *get_secflag_string(uint64_t flag) {
    uint8_t flagindex = 0;
    if ((uint8_t)flag & SHF_WRITE) {secflagstr[flagindex++] = 'W';}
    if ((uint8_t)flag & SHF_ALLOC) {secflagstr[flagindex++] = 'A';}
    if ((uint8_t)flag & SHF_EXECINSTR) {secflagstr[flagindex++] = 'X';}
    if ((uint8_t)flag & SHF_INFO_LINK) {secflagstr[flagindex] = 'I';}
    return secflagstr;
}

