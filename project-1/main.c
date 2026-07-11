#include <stdio.h>
#include <stdbool.h>
#include "memory.h"

int main(void) {
    print_stack();
    print_heap();
    print_global();
    print_struct();
    print_array();
    print_string();
    print_pointer();

    run_mem_leak_bug(false);
    run_uaf_bug(false);
    run_invalid_read_bug(false);
    run_segmentation_fault(false);
    run_endless_recursion(false);

    return 0;
}
