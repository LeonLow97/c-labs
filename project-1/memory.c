#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "memory.h"

// Global Variables are stored in Data Segment (.data)
// High addresses
// +-------------------+
// |      Stack        |
// |         ↓         |
// +-------------------+
// |                   |
// |    (free space)   |
// |                   |
// +-------------------+
// |         ↑         |
// |       Heap        |
// +-------------------+
// | .bss              |  <- uninitialized globals/statics
// | .data             |  <- initialized globals/statics
// | .rodata           |  <- string literals, const data
// | .text             |  <- program instructions
// +-------------------+
// Low addresses
//
// Global variable, `static` keyword used to indicate it's only used within `memory.c`
static int global_value = 500;

void print_stack(void) {
    int i = 42;

    printf("========== STACK ==========\n");
    printf("Value: %d\n", i);
    printf("Address: %p\n", (void *)&i);
}

void print_heap(void) {
    int *p = malloc(sizeof(*p)); // allocated 4 bytes

    if (p == NULL) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    *p = 12345;

    printf("========== HEAP ==========\n");
    printf("Value: %d\n", *p);
    printf("Address: %p\n", (void *)p);

    free(p);
}

void print_global(void) {
    printf("========== GLOBAL ==========\n");
    printf("Value: %d\n", global_value);
    printf("Address: %p\n", (void *)&global_value);
}

typedef struct {
    int age;
    char *name;
    char *hobbies[10]; // array of 10 string pointers
    float *net_worth;
} User;

void print_struct(void) {
    User user;

    user.age = 29;
    user.name = "Leon";

    user.hobbies[0] = "Basketball";
    user.hobbies[1] = "Sleeping";
    user.hobbies[2] = "Mobile Legends";
    user.hobbies[3] = NULL; // common convention to terminate the used portion with NULL

    float current_net_worth = 9999.9f;
    user.net_worth = &current_net_worth;

    printf("========== STRUCT ==========\n");
    printf("Struct Address: %p\n", (void *)&user);
    printf("user.age Address: %p\n", (void *)&user.age);
    printf("user.name Address: %p\n", (void *)&user.name); // `user.name` points to first memory block of `char *` but `&user.name` points to entire block containing the `char *`
    printf("user.name First Mem Block Address: %p\n", (void *)user.name); // `user.name` points to first memory block of `char *` but `&user.name` points to entire block containing the `char *`
    printf("user.hobbies Address: %p\n", (void *)user.hobbies);
    printf("user.net_worth Address: %p\n", (void *)&user.net_worth);
    printf("user.net_worth First Mem Block Address: %p\n", (void *)user.net_worth);

    printf("user.age Value: %d\n", user.age);
    printf("user.name Value: %s\n", user.name);

    for (int i = 0; user.hobbies[i] != NULL; i ++)
        printf("user.hobby Value: %s\n", user.hobbies[i]);
    
    printf("user.net_worth: %f\n", *user.net_worth);
}

void print_array(void) {
    int int_arr[5] = {1, 2, 3, 4, 5};
    char char_arr[5] = {'A', 'B', 'C', 'D', '\0'};

    printf("========== ARRAY ==========\n");
    // These are the same, arrays decay pointers to their first element
    printf("Int Array Address: %p\n", (void *)&int_arr); // address of entire array
    printf("Int Array Address: %p\n", (void *)int_arr); // address of first element
    printf("Char Array Address: %p\n", (void *)&char_arr);
    printf("Char Array Address: %p\n", (void *)char_arr);

    size_t int_arr_length = sizeof(int_arr) / sizeof(int_arr[0]);
    for (size_t i = 0; i < int_arr_length; i++) {
        printf("int_arr[%zu] = %d, address = %p\n",
            i, int_arr[i], (void *)&int_arr[i]);
    }

    size_t char_arr_length = sizeof(char_arr) / sizeof(char_arr[0]);
    for (size_t i = 0; i < char_arr_length; i++) {
        printf("char_arr[%zu] = %c, address = %p\n",
            i, char_arr[i], (void *)&char_arr[i]);
    }
}

void print_string(void) {
    char *string = "Leon"; // string literal, do not modify! string[0] = 'B'; results in undefined
    char char_arr[] = "Leon Array"; // character array, can modify

    // For dynamically allocated string, use heap instead of stack
    // Stack is usually 1-8 MB which runs out fast causing StackOverflow error
    // To allocate dynamically, use the heap instead as it is limited to machine's physical RAM

    char *dynamic_string = "Hello, my name is Leon! Nice to meet you!";
    // strlen does not include '\0' so need to add 1
    size_t dynamic_string_length = strlen(dynamic_string) + 1;
    char *new_string = malloc(sizeof(char) * dynamic_string_length);
    if (new_string == NULL) {
        fprintf(stderr, "failed to allocate a dynamic string\n");
        return;
    }
    memcpy(new_string, dynamic_string, dynamic_string_length); // specify how many bytes to copy

    printf("========== STRING ==========\n");
    printf("String Literal Address: %p\n", (void *)string);
    printf("Char Arr Address: %p\n", (void *)char_arr);
    printf("Dynamically Allocated String Address: %p\n", (void *)new_string);

    printf("String Literal Value: %s\n", string);
    printf("Char Array Value: %s\n", char_arr);
    printf("Dynamically Allocated Value: %s\n", new_string);

    free(new_string);
}

void print_pointer(void) {
    int num = 1007;
    int *num_ptr = &num;

    printf("========== POINTER (STACK MEMORY) ==========\n");
    printf("Pointer Variable Address: %p\n", (void *)&num_ptr); // where the pointer lives in mem
    printf("Pointer Value (Stack Address): %p\n", (void *)num_ptr); // address of actual 'num' in memory
    printf("Dereferenced Value: %d\n", *num_ptr); // dereferenced value

    char *actual_name = "Leon"; // Points to ROData segment initially
    size_t name_length = strlen(actual_name) + 1;
    char *name = malloc(sizeof(char) * name_length);
    if (name == NULL) {
        fprintf(stderr, "malloc failed\n");
        return;
    }

    // Copy the actual string "Leon" into the newly allocated memory
    strcpy(name, actual_name);

    printf("========== POINTER (HEAP MEMORY) ==========\n");
    printf("Pointer Variable Address: %p\n", (void *)&name); // where the pointer variable "name" lives (Stack)
    printf("Pointer Value (Heap Address): %p\n", (void *)name); // the address "name" points to (Heap)
    printf("Dereferenced Value: %s\n", name);

    free(name);

    int *global_value_pointer = &global_value;

    printf("========== POINTER (GLOBAL) ==========\n");
    printf("Pointer Variable Address: %p\n", (void *)&global_value_pointer);
    printf("Pointer Value (Referenced Address): %p\n", (void *)&global_value);
    printf("Dereferenced Value: %d\n", *global_value_pointer);
}

void run_mem_leak_bug(bool triggered) {
    char *src = "Leon";
    char *name = malloc(strlen(src) + 1); // memory address of 5 bytes from Heap
    if (name == NULL) {
        fprintf(stderr, "malloc failed\n");
        return;
    }
    // memcpy(name, "Leon", 5);
    strcpy(name, src); // more dynamic, no need care about the length and extra byte for NUL terminator
    
    if (!triggered) {
        printf("freeing memory\n");
        free(name);
    } else {
        printf("Introducing memory leak bug by not freeing the allocated memory.\n");
    }
}

// uaf --> Use-After-Free
void run_uaf_bug(bool triggered) {
    char *name;
    char *alloc_name = malloc(sizeof(char) * 5); // memory address of 5 bytes from Heap
    if (alloc_name == NULL) {
        fprintf(stderr, "malloc failed\n");
        return;
    }
    name = alloc_name;
    // memcpy(alloc_name, "Leon", 5);
    strcpy(alloc_name, "Leon"); // more dynamic, no need care about the length and extra byte for NUL terminator

    free(name); // comment out to view UAF bug

    if (!triggered) {
        name = NULL; // good habit is to clear the pointer so it can't be misused.
    } else {
        name[0] = 'B';
        printf("Introducing UAF bug by accessing freed memory: %c\n", name[0]);
    }
}

void run_invalid_read_bug(bool triggered) {
    char *name = malloc(sizeof(char) * 5); // memory address of 5 bytes from Heap
    if (name == NULL) {
        fprintf(stderr, "malloc failed\n");
        return;
    }
    strcpy(name, "Leon");

    if (triggered) {
        char out_of_bounds_char = name[5];
        printf("accessing out of bounds memory: %c\n", out_of_bounds_char);
    }

    free(name);
}

void run_segmentation_fault(bool triggered) {
    // 1. Dereferencing a NULL pointer
    int *ptr = NULL;
    if (triggered) {
        *ptr = 10;
    }

    // 2. Going Out of Bounds (Buffer Overflow)
    // C doesn't check array bounds for you if you read or write past the end of an array.
    int arr[5] = {1, 2, 3, 4, 5};
    if (triggered) {
        arr[10] = 5;
    }

    // 3. Modifying Read-Only Memory (String Literals)
    char *str = "Hello"; // stored in read-only section of memory
    if (triggered) {
        str[0] = 'L'; // Seg fault: Attempting to modify read-only text memory
    }

    // 4. Using Uninitialized Pointers
    // If you declare a pointer but don't point it anywhere, it contains garbage data (whatever random
    // bits were left in memory). Trying to dereference if means you are accessing a random memory address.
    int *un_ptr;
    if (triggered) {
        *un_ptr = 5;
    }
}

// Stack Overflow (Infinite Recursion)
// Everytime a function is called, it allocates memory on the stack. If a function calls
// itself infinitely, the stack runs out of space and overflows into forbidden territory.
void run_endless_recursion(bool triggered) {
    if (triggered) {
        run_endless_recursion(true);
    }
}