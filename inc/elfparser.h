#ifndef _ELF_PARSER_H
#define _ELF_PARSER_H

#include <stdint.h>

#define EI_NIDENT (16)

// define offsets in identy arrays
#define EI_CLASS          0x04
#define EI_DATA           0x05
#define EI_VERSION        0x06
#define EI_OSABI          0x07
#define EI_ABIVERSION     0x08

#define MAGIC_SIZE        4


typedef struct
{
    unsigned char	e_ident[EI_NIDENT];
    uint16_t        e_type;
    uint16_t        e_machine;
    uint32_t        e_version;
    uint64_t        e_entry;
    uint64_t        e_phoff;
    uint64_t        e_shoff;
    uint32_t        e_flags;
    uint16_t        e_ehsize;
    uint16_t        e_phentsize;
    uint16_t        e_phnum;
    uint16_t        e_shentsize;
    uint16_t        e_shnum;
    uint16_t        e_shstrndx; // this index points to the section number that contains the string table
} elf64_hdr_t;


typedef struct {
    uint32_t   sh_name; // sh_name represents offset in string table
    uint32_t   sh_type;
    uint64_t   sh_flags;
    uint64_t   sh_addr;
    uint64_t   sh_offset;
    uint64_t   sh_size;
    uint32_t   sh_link;
    uint32_t   sh_info;
    uint64_t   sh_addralign;
    uint64_t   sh_entsize;
} elf64_shdr_t;



typedef enum {
    VALID_ELF = 0,
    INVALID_ELF
} elf_ret_t;

elf_ret_t elf_show_header(elf64_hdr_t *elfheader);
void elf_show_sec_header(elf64_hdr_t *elfheader, int fd);

#endif
