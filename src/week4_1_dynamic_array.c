/*
 * week4_1_dynamic_array.c
 * Author: Serhii Voitov
 * Student ID: 251ADC006
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

static int fill_numbers(int *buf, int count)
{
    int *p = buf;
    int *stop = buf + count;

    while (p < stop) {
        if (scanf("%d", p) != 1)
            return 0;
        p++;
    }
    return 1;
}

static long total_of(const int *buf, int count)
{
    long acc = 0;
    while (count-- > 0)
        acc += *buf++;
    return acc;
}

int main(void)
{
    int count;
    int *numbers;
    int status = 0;

    printf("Enter number of elements: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        puts("Invalid size.");
        return 1;
    }

    numbers = (int *)malloc(sizeof(int) * (size_t)count);
    if (!numbers) {
        puts("Memory allocation failed.");
        return 1;
    }

    printf("Enter %d integers: ", count);
    if (!fill_numbers(numbers, count)) {
        puts("Invalid input.");
        status = 1;
        goto cleanup;
    }

    {
        long total = total_of(numbers, count);
        printf("Sum = %ld\n", total);
        printf("Average = %.2f\n", total / (double)count);
    }

cleanup:
    free(numbers);
    return status;
}
