#include <stdio.h>

/*
    Task:
    Write a function `long long factorial(int n)` that computes n!
    using a loop (not recursion).

    In main():
      - Ask user for an integer n
      - If n is negative, print an error and exit
      - Otherwise, call factorial and print the result
*/

long long factorial(int n) {
    long long result = 1;           /* 0! and 1! are both 1 */

    for (int i = 2; i <= n; i++) {  /* multiply 2 * 3 * ... * n */
        result = result * i;
    }

    return result;
}

int main(void) {
    int n;

    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Input error: please type a whole number.\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: factorial is not defined for negative numbers.\n");
        return 1;
    }

    if (n > 20) {
        /* 21! does not fit into a long long (max is about 9.2 * 10^18) */
        printf("Error: n must be 20 or less, otherwise the result overflows.\n");
        return 1;
    }

    printf("%d! = %lld\n", n, factorial(n));

    return 0;
}
