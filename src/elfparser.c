#include <stdio.h>
#include <string.h>
#include "../inc/elfparser.h"
#include "../inc/ident_utils.h"

elf_ret_t elf_show_header(elf64_hdr_t *elfheader) {
    char magic[4];
    memcpy(magic, elfheader->e_ident, 4);


    printf("Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", elfheader->e_ident[i]);
    }
    printf("\n");

    printf("Class:      \t\t\t\t %s\n", get_class_string(elfheader));
    printf("Data:       \t\t\t\t %s\n", get_data_string(elfheader));
    printf("Version:    \t\t\t\t %d\n", elfheader->e_ident[EI_VERSION]);
    printf("OS/ABI:     \t\t\t\t %s\n", get_osabi_string(elfheader));
    printf("ABI Version:\t\t\t\t %d\n", elfheader->e_ident[EI_ABIVERSION]);
    printf("Type:       \t\t\t\t %s\n", get_elftype_string(elfheader));
    printf("Machine:    \t\t\t\t %x\n", elfheader->e_machine);
    printf("Version:    \t\t\t\t 0x%x\n", elfheader->e_version);
    printf("Entry point address: \t\t\t 0x%lx\n", elfheader->e_entry);
    printf("Start of program headers: \t\t %ld\n", elfheader->e_phoff);
    printf("Start of section headers: \t\t %ld\n", elfheader->e_shoff);
    printf("Flags:      \t\t\t\t 0x%x\n", elfheader->e_flags);
    printf("Size of this header: \t\t\t %d\n", elfheader->e_ehsize);
    printf("Size of program header:   \t\t %d\n", elfheader->e_phentsize);
    printf("Number of program headers: \t\t %d\n", elfheader->e_phnum);
    printf("Size of section headers: \t\t %d\n", elfheader->e_shentsize);
    printf("Number of section headers: \t\t %d\n", elfheader->e_shnum);
    printf("Sectin header string table index: \t %d\n", elfheader->e_shstrndx);

    return VALID_ELF;
}

