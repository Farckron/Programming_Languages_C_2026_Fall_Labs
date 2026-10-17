/*
 * week4_3_struct_database.c
 * Author: Serhii Voitov
 * Student ID: 251ADC006
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

static int read_record(struct Student *rec, int number)
{
    printf("Enter data for student %d: ", number);
    return scanf("%49s %d %f", rec->name, &rec->id, &rec->grade) == 3;
}

static void print_table(const struct Student *table, int size)
{
    const struct Student *row = table;

    printf("\n%-6s %-11s %s\n", "ID", "Name", "Grade");
    while (row < table + size) {
        printf("%-6d %-11s %.1f\n", row->id, row->name, row->grade);
        row++;
    }
}

int main(void)
{
    int size;
    int k = 0;
    int rc = 0;
    struct Student *table;

    printf("Enter number of students: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        puts("Invalid number.");
        return 1;
    }

    table = malloc(size * sizeof(struct Student));
    if (table == NULL) {
        puts("Memory allocation failed.");
        return 1;
    }

    while (k < size) {
        if (!read_record(table + k, k + 1)) {
            puts("Invalid input.");
            rc = 1;
            break;
        }
        k++;
    }

    if (rc == 0)
        print_table(table, size);

    free(table);
    return rc;
}
