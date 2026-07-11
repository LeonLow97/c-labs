#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>

void print_stack(void);
void print_heap(void);
void print_global(void);
void print_struct(void);
void print_array(void);
void print_string(void);
void print_pointer(void);

void run_mem_leak_bug(bool triggered);
void run_uaf_bug(bool triggered);
void run_invalid_read_bug(bool triggered);
void run_segmentation_fault(bool triggered);
void run_endless_recursion(bool triggered);

#endif
