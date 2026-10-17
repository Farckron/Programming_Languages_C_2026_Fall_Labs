/*
 * week4_2_struct_student.c
 * Author: Serhii Voitov
 * Student ID: 251ADC006
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Define a 'Student' struct with name, id and grade, create two
 *   instances with the values from the instructions, and print them.
 *
 *   This program reads no input. Output must match the format in the
 *   Week 4 instructions exactly (it is checked by the autograder).
 */

#include <stdio.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int id;
    float grade;
} Student;

static Student make_student(const char *name, int id, float grade)
{
    Student st;
    strcpy(st.name, name);
    st.id = id;
    st.grade = grade;
    return st;
}

static void show(int number, Student st)
{
    printf("Student %d: %s, ID: %d, Grade: %.1f\n", number, st.name, st.id, st.grade);
}

int main(void)
{
    Student first = make_student("Alice Johnson", 1001, 9.1f);
    Student second = make_student("Bob Smith", 1002, 8.7f);

    show(1, first);
    show(2, second);
    return 0;
}
