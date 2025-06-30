# Parsing Section Headers
## Section Headers Offset
   1. From the ELF headers, we take `e_shoff` field to seek to the section headers.
   2. Create an array of section headers.
   3. Use `e_shstrndx` as an index to acquire string table header.
   4. Seek to the string table data using `sh_offset` of the string table header.
   5. Read the data of the string table into a string.
   6. Now that we have the string table and the section headers, we can iterate through the enteries using `e_shnum` to print out the data of all sections.
