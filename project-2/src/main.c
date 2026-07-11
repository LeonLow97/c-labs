#include <stdio.h>
#include <stdlib.h>
#include "employee.h"

int main(void) {
    ReadEmployeeMetadata read_employee_metadata = read_employee("data/employees.txt");
    printf("number of employees: %zu\n", read_employee_metadata.count);

    Employee *employees = read_employee_metadata.employees;
    if (employees == NULL) {
        fprintf(stderr, "failed to read employees\n");
        return 1;
    }

    for (size_t i = 0; i < read_employee_metadata.count ; i++) {
        Employee employee = employees[i];
        printf("ID: %d | Name: %s | Department: %s\n", employee.id, employee.name, employee.dept);
    }

    free(employees);

    return 0;
}
