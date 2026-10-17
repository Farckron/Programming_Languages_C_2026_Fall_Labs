// week5_task1_file_io.c
// Name: Serhii  Surname: Voitov  Student ID: 251ADC006
//
// Task 1: Read and write data from text files
// Week 5 – Files & Modular Programming
// TODO: Fill in the missing parts marked below.
//
// Build: make lab5   Run: ./bin/week5_task1_file_io

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

static const char *const greeting[] = {
    "Hello, file I/O in C!",
    "This is another line.",
};
#define GREETING_LINES ((int)(sizeof greeting / sizeof greeting[0]))

static int write_greeting(const char *path)
{
    FILE *out = fopen(path, "w");
    int i;

    if (!out)
        return -1;
    for (i = 0; i < GREETING_LINES; i++)
        fprintf(out, "%s\n", greeting[i]);
    fclose(out);
    return 0;
}

static int echo_file(const char *path)
{
    char buf[LINE_LEN];
    int seen = 0;
    FILE *in = fopen(path, "r");

    if (!in)
        return -1;
    puts("Reading contents:");
    while (fgets(buf, LINE_LEN, in)) {
        fputs(buf, stdout);
        ++seen;
    }
    fclose(in);
    return seen;
}

int main(int argc, char *argv[])
{
    const char *path = (argc > 1) ? argv[1] : DEFAULT_FILENAME;
    int lines;

    printf("Writing lines to %s...\n", path);
    if (write_greeting(path) != 0) {
        perror(path);
        return EXIT_FAILURE;
    }

    lines = echo_file(path);
    if (lines < 0) {
        perror(path);
        return EXIT_FAILURE;
    }

    printf("Lines read: %d\n", lines);
    return EXIT_SUCCESS;
}
