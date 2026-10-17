// week5_task3_student_management_system.c
// Name: Serhii  Surname: Voitov  Student ID: 251ADC006
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

int  load_students(Student arr[], int max);
int  save_students(const Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                if (save_students(students, count) == -1)
                    fprintf(stderr, "Could not write %s\n", DATA_FILE);
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

int load_students(Student arr[], int max)
{
    char buf[LINE_LEN];
    Student *slot = arr;
    FILE *in = fopen(DATA_FILE, "r");

    if (!in)
        return 0;

    while (slot - arr < max && fgets(buf, sizeof buf, in)) {
        if (sscanf(buf, "%49[^,],%d,%f", slot->name, &slot->id, &slot->gpa) == 3)
            slot++;
    }
    fclose(in);
    return (int)(slot - arr);
}

int save_students(const Student arr[], int count)
{
    const Student *p;
    FILE *out = fopen(DATA_FILE, "w");

    if (!out)
        return -1;
    for (p = arr; p < arr + count; p++)
        fprintf(out, "%s,%d,%.2f\n", p->name, p->id, p->gpa);
    fclose(out);
    return 0;
}

static int valid_name(const char *s)
{
    size_t len = strlen(s);
    return len > 0 && len < NAME_LEN && strchr(s, ',') == NULL;
}

static int parse_id(const char *s, int *id)
{
    char *rest;
    long v = strtol(s, &rest, 10);

    if (rest == s || *rest != '\0')
        return 0;
    *id = (int)v;
    return 1;
}

static int parse_gpa(const char *s, float *gpa)
{
    char *rest;
    double v = strtod(s, &rest);

    if (rest == s || *rest != '\0' || !(v >= 0.0 && v <= 4.0))
        return 0;
    *gpa = (float)v;
    return 1;
}

void add_student(Student arr[], int *count)
{
    char name[LINE_LEN], id_buf[LINE_LEN], gpa_buf[LINE_LEN];
    Student fresh;

    if (*count >= MAX_STUDENTS) {
        puts("Cannot add more students (limit reached).");
        return;
    }

    if (read_line("Enter name: ", name, sizeof name) ||
        read_line("Enter ID: ", id_buf, sizeof id_buf) ||
        read_line("Enter GPA: ", gpa_buf, sizeof gpa_buf))
        return;

    if (!valid_name(name) || !parse_id(id_buf, &fresh.id) || !parse_gpa(gpa_buf, &fresh.gpa)) {
        puts("Invalid input. Student not added.");
        return;
    }

    strcpy(fresh.name, name);
    arr[(*count)++] = fresh;
    puts("Student added successfully!");
}

void list_students(const Student arr[], int count)
{
    int i = 0;

    if (count <= 0) {
        puts("No students found.");
        return;
    }
    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    while (i < count) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
        i++;
    }
}
