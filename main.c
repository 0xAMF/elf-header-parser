#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "inc/elfparser.h"


char buffer[500];
elf64_hdr_t elfheader;

int main(int argc, char **argv)
{
    // check user input
    if (argc <= 1) {
        printf("usage: ./myreadelfh <elf_binary>\n");
        return -1;
    }

    // open file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open error: ");
        return 1;
    }

    // read file
    ssize_t bytes_read = read(fd, buffer, sizeof(elf64_hdr_t));
    if (bytes_read == -1) {
        perror("file error: ");
    }

    // close file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    // copy the data inside our struct
    memcpy(&elfheader, buffer, sizeof(elf64_hdr_t));

    if(elf_show_header(&elfheader) != VALID_ELF) {
        printf("File is not ELF!\n");
        return 2;
    }

    return 0;
}


