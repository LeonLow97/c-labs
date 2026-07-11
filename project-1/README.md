- [C Memory Management](#c-memory-management)
  - [Problem Statement](#problem-statement)
  - [Success Criteria](#success-criteria)
  - [Project Structure](#project-structure)
  - [Setup](#setup)

# C Memory Management

A small C project for learning memory management fundamentals.

## Problem Statement

Understand how memory works in C by exploring stack, heap, global variables, pointers, arrays, structs, and common memory bugs.

## Success Criteria

- Demonstrate stack, heap, global, and read-only memory.
- Allocate and free memory correctly.
- Understand pointers and pointer addresses.
- Demonstrate common memory errors:
  - Memory leak
  - Use-after-free
  - Out-of-bounds access
  - Segmentation fault

- Analyze memory errors using Valgrind.

## Project Structure

```text
.
├── Dockerfile
├── Makefile
├── main.c
├── memory.c
├── memory.h
└── README.md
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

Run Valgrind:

```bash
make valgrind
```
