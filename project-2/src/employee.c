#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

ReadEmployeeMetadata read_employee(char *file_loc) {
    ReadEmployeeMetadata read_employee_metadata;
    read_employee_metadata.employees = NULL;
    read_employee_metadata.count = 0;

    size_t emp_buffer_cap = 2;
    size_t emp_count = 0;

    Employee *emp_buffer = malloc(sizeof(Employee) * emp_buffer_cap);
    if (emp_buffer == NULL) {
        fprintf(stderr, "failed to allocate heap memory to employee buffer\n");
        return read_employee_metadata;
    }

    FILE *fp = fopen(file_loc, "r");
    if (fp == NULL) {
        fprintf(stderr, "failed to open file: %s\n", file_loc);
        free(emp_buffer);
        return read_employee_metadata;
    }

    size_t line_cap = 16;

    char *line_buffer = malloc(sizeof(char) * line_cap);
    if (line_buffer == NULL) {
        fprintf(stderr, "failed to allocate heap memory to line buffer\n");
        free(emp_buffer);
        fclose(fp);
        return read_employee_metadata;
    }

    // fgets():
    // - first argument: where to start writing
    // - second argument: how many bytes can I safely write (including the terminating '\0')
    // Returns NULL if error or end of file (EOF) reached

    // 2 while loops
    // - Outer loop: read one employee
    // - Inner loop: keep calling fgets() until the entire line has been read
    while (1) {
        size_t line_used_bytes = 0;

        // Read chunks from the current line until the entire line has been assembled, checks if EOF reached
        while (fgets(
            line_buffer + line_used_bytes, // where to start writing 
            sizeof(char) * (line_cap - line_used_bytes), // how many bytes are still available
            fp
        ) != NULL) {
            line_used_bytes = strlen(line_buffer);
            // line_used_bytes += strlen(line_buffer + line_used_bytes); // small performance optimization but difficult to understand
            // strlen() starts at the address pointed to by line_buffer and counts
            // characters until it reaches the first '\0'.

            if (strchr(line_buffer, '\n') != NULL)
                // End of line reached, means 1 employee row read, stop reallocating
                break;

            // End of line not reached, need to realloc more to line buffer
            size_t new_line_cap = line_cap * 2;
            char *tmp_line_buffer = realloc(line_buffer, new_line_cap);
            if (tmp_line_buffer == NULL) {
                fprintf(stderr, "failed to realloc heap memory to line buffer\n");
                free(emp_buffer);
                free(line_buffer);
                fclose(fp);
                return read_employee_metadata;
            }

            line_buffer = tmp_line_buffer; // successfully realloc more heap memory to line buffer
            line_cap = new_line_cap;
        }

        if (line_used_bytes == 0)
            // If EOF reached during fgets(), we check if number of bytes read if 0, to break out of outer loop
            break;
        
        // Remove newline before parsing employee
        char *newline = strchr(line_buffer, '\n');
        if (newline != NULL)
            *newline = '\0';
        
        // Parse Employee
        Employee employee;
        if (sscanf(
            line_buffer, 
            "ID:%d,NAME:%63[^,],DEPT:%63[^\r]",
            &employee.id,
            employee.name,
            employee.dept
        ) != 3) {
            fprintf(stderr, "invalid employee record\n");
            continue;
        }

        if (emp_count == emp_buffer_cap) {
            size_t new_emp_cap = emp_buffer_cap * 2;
            Employee *tmp_emp_buffer = realloc(emp_buffer, sizeof(Employee) * new_emp_cap);
            if (tmp_emp_buffer == NULL) {
                fprintf(stderr, "failed to realloc heap memory to emp buffer\n");
                free(emp_buffer);
                free(line_buffer);
                fclose(fp);
                return read_employee_metadata;
            }
            emp_buffer = tmp_emp_buffer;
            emp_buffer_cap = new_emp_cap;
        }
        emp_buffer[emp_count++] = employee;
    }

    free(line_buffer);
    fclose(fp);

    read_employee_metadata.employees = emp_buffer;
    read_employee_metadata.count = emp_count;

    return read_employee_metadata;
}
