#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/elfparser.h"
#include "../inc/ident_utils.h"

const char realmagic[MAGIC_SIZE] = {0x7f, 0x45, 0x4c, 0x46};

elf_ret_t elf_show_header(elf64_hdr_t *elfheader) {
    char magic[MAGIC_SIZE];
    memcpy(magic, elfheader->e_ident, 4);

    if (memcmp(realmagic, magic, MAGIC_SIZE) != 0) {
        return INVALID_ELF;
    }

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
    printf("Section header string table index: \t %d\n", elfheader->e_shstrndx);

    return VALID_ELF;
}


void elf_show_sec_header(elf64_hdr_t *elfheader, int fd) {
    // get section header offset, section number and section string index
    uint64_t shoff = elfheader->e_shoff;
    uint16_t shnum = elfheader->e_shnum;
    uint16_t shentsize = elfheader->e_shentsize;
    uint16_t shstrndx = elfheader->e_shstrndx;
    // table size of section headers
    uint32_t shtablesize = shnum * shentsize;

    // seek into the file to section headers
    if (lseek(fd, shoff, SEEK_SET) == -1) {
        perror("lseek error: ");
        close(fd);
        exit(EXIT_FAILURE);
    }
    // create section header array and read headers
    elf64_shdr_t *shdrs = (elf64_shdr_t *)malloc(shtablesize);
    if (read(fd, shdrs, shtablesize) != shtablesize) {
        perror("read error: ");
        free(shdrs);
        close(fd);
        exit(EXIT_FAILURE);
    }
    // read section header string tables using string index
    elf64_shdr_t shstrtab_hdr = shdrs[shstrndx];
    char *shstrtab = (char *)malloc(shstrtab_hdr.sh_size);
    // seek to string table section data
    if (lseek(fd, shstrtab_hdr.sh_offset, SEEK_SET) == -1) {
        perror("failed to seek to string table: ");
        free(shstrtab);
        free(shdrs);
        close(fd);
        exit(EXIT_FAILURE);
    }
    // read string table section data
    if (read(fd, shstrtab, shstrtab_hdr.sh_size) != shstrtab_hdr.sh_size) {
        perror("read error: ");
        free(shstrtab);
        free(shdrs); close(fd);
        exit(EXIT_FAILURE);
    }

    // iterate through sections and print out their data
    printf("[Nr] Name\t\t   Type\t       Address              Offset\n");
    printf("     Size\t\t   EntSize     Flags  Link  Info   Align\n");
    for (int i = 0; i < shnum; i++) {
        printf("[%-2d] %-20s  %-10s  %016lx     %08lx\n", i, (shstrtab + shdrs[i].sh_name),
                get_sectype_string(shdrs[i].sh_type),
                shdrs[i].sh_addr,
                shdrs[i].sh_offset);
        printf("     %016lx %016lx %s\t%d\t%d\t%ld\n", shdrs[i].sh_size,
                shdrs[i].sh_entsize,
                get_secflag_string(shdrs[i].sh_flags),
                shdrs[i].sh_link,
                shdrs[i].sh_info,
                shdrs[i].sh_addralign);

        get_secflag_string(shdrs[i].sh_flags);
    }

}
