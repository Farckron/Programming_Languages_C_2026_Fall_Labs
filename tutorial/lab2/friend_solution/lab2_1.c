#include <stdio.h>

/*
    Task:
    Write a function `int sum_to_n(int n)` that computes
    the sum of all integers from 1 up to n using a for loop.

    In main():
      - Ask user for a positive integer n
      - If n < 1, print an error
      - Otherwise, call sum_to_n and print the result
*/

int sum_to_n(int n) {
    int total = 0;                  /* running sum, starts empty */

    for (int i = 1; i <= n; i++) {  /* i takes the values 1, 2, ..., n */
        total = total + i;
    }

    return total;
}

int main(void) {
    int n;

    printf("Enter a positive integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Input error: please type a whole number.\n");
        return 1;
    }

    if (n < 1) {
        printf("Error: n must be 1 or bigger (you typed %d).\n", n);
        return 1;
    }

    int result = sum_to_n(n);
    printf("1 + 2 + ... + %d = %d\n", n, result);

    return 0;
}
