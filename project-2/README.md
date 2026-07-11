# Dynamic Employee File Reader

A small C project for learning dynamic memory allocation, file I/O, and buffer management.

## Problem Statement

Read an employee data file of unknown size into dynamically allocated memory while safely handling file I/O, dynamic buffer resizing, and malformed input.

## Success Criteria

- Read employee records from a text file.
- Dynamically grow buffers using `realloc()`.
- Parse employee data safely.
- Handle allocation and file I/O errors gracefully.
- Return employee data through a clean API.
- Free all allocated memory without memory leaks.

## Project Structure

```text
.
├── data
│   └── employees.txt
├── Dockerfile
├── Makefile
└── src
    ├── employee.c
    ├── employee.h
    └── main.c
```

## Setup

Build the Docker image:

```bash
make build
```

Start the development container:

```bash
make run
```

Run the project with Valgrind:

```bash
make valgrind
```

## Concepts Covered

- Dynamic memory allocation (`malloc`, `realloc`, `free`)
- File I/O (`fopen`, `fgetc`, `fclose`)
- Dynamic array resizing
- Dynamic string buffering
- Safe parsing with `sscanf`
- Modular C programming
- Memory leak prevention
- Error handling
