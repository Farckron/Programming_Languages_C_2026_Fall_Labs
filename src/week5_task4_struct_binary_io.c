// week5_task4_struct_binary_io.c   (BONUS)
// Name: Serhii  Surname: Voitov  Student ID: 251ADC006
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

int  save_student_binary(const Student *s, const char *filename);
int  load_student_binary(const char *filename, Student *out);
long file_size(const char *filename);

int save_student_binary(const Student *s, const char *filename)
{
    FILE *f = fopen(filename, "wb");
    int rc = -1;

    if (f) {
        if (fwrite(s, sizeof(Student), 1, f) == 1)
            rc = 0;
        fclose(f);
    }
    return rc;
}

int load_student_binary(const char *filename, Student *out)
{
    FILE *f = fopen(filename, "rb");
    int rc = -1;

    if (f) {
        if (fread(out, sizeof(Student), 1, f) == 1)
            rc = 0;
        fclose(f);
    }
    return rc;
}

long file_size(const char *filename)
{
    FILE *f = fopen(filename, "rb");
    long bytes = -1;

    if (f) {
        if (fseek(f, 0, SEEK_END) == 0)
            bytes = ftell(f);
        fclose(f);
    }
    return bytes;
}

static int save_student_text(const Student *s, const char *filename)
{
    FILE *f = fopen(filename, "w");

    if (!f)
        return -1;
    fprintf(f, "%s %d %.2f\n", s->name, s->age, s->gpa);
    fclose(f);
    return 0;
}

int main(void)
{
    const char *bin_path = "student.bin";
    const char *txt_path = "student.txt";
    Student original = {0};
    Student copy = {0};

    strcpy(original.name, "Alice");
    original.age = 21;
    original.gpa = 3.75f;

    puts("Saving student in binary format...");
    if (save_student_binary(&original, bin_path) || save_student_text(&original, txt_path)) {
        perror("save");
        return EXIT_FAILURE;
    }

    puts("Loading student from binary file...");
    if (load_student_binary(bin_path, &copy)) {
        perror(bin_path);
        return EXIT_FAILURE;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", copy.name, copy.age, copy.gpa);
    printf("Text file size: %ld bytes\n", file_size(txt_path));
    printf("Binary file size: %ld bytes\n", file_size(bin_path));
    return EXIT_SUCCESS;
}
