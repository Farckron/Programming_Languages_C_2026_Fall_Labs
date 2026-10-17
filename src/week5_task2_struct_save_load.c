// week5_task2_struct_save_load.c
// Name: Serhii  Surname: Voitov  Student ID: 251ADC006
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// TODO: Complete the function implementations and the file handling logic.
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int save_student(const Student *s, const char *filename);
int load_student(const char *filename, Student *out);

int save_student(const Student *s, const char *filename)
{
    FILE *f;
    int ok;

    if ((f = fopen(filename, "w")) == NULL)
        return -1;
    ok = fprintf(f, "%s %d %.2f\n", s->name, s->age, s->gpa) > 0;
    if (fclose(f) != 0)
        ok = 0;
    return ok ? 0 : -1;
}

int load_student(const char *filename, Student *out)
{
    FILE *f;
    int n;

    if ((f = fopen(filename, "r")) == NULL)
        return -1;
    n = fscanf(f, "%49s %d %f", out->name, &out->age, &out->gpa);
    fclose(f);
    return (n == 3) ? 0 : -1;
}

int main(void)
{
    const char *path = "student.txt";
    Student original = {0};
    Student copy = {0};

    strcpy(original.name, "Alice");
    original.age = 21;
    original.gpa = 3.75f;

    puts("Saving student to file...");
    if (save_student(&original, path) == -1) {
        perror(path);
        return EXIT_FAILURE;
    }

    puts("Loading student from file...");
    if (load_student(path, &copy) == -1) {
        fprintf(stderr, "%s: could not read a valid record\n", path);
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", copy.name, copy.age, copy.gpa);
    return EXIT_SUCCESS;
}
