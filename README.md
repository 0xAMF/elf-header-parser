# ELF Header Parser

A simple ELF (Executable and Linkable Format) header parser written in C. This tool allows you to extract and display key metadata from ELF binary files, such as the ELF header, section headers, and string table.

## 🧠 Features
- Parses ELF64 headers.
- Displays:
  - ELF magic and file class
  - Entry point address
  - Section headers and types
  - Section names via the string table
- Portable and minimal C code.

## Usage

### 1. Build the parser

```bash
make
```

This will generate an executable named `shelf`.

### 2. Run the parser on an ELF binary

```bash
./shelf /path/to/binary
```

Example:

```bash
./shelf /bin/ls
```
---

###  TODO

- Add support for ELF32
- Display program headers
- Add symbol table parsing
