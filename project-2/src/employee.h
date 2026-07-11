#ifndef EMPLOYEE_H
#define EMPLOYEE_H

typedef struct {
    int id;
    char name[64];
    char dept[64];
} Employee;

typedef struct {
    Employee *employees;
    size_t count;
} ReadEmployeeMetadata;

ReadEmployeeMetadata read_employee(char *file_loc);

#endif
