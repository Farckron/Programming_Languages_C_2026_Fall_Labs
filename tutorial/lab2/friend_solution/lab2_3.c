#include <stdio.h>

/*
    Task:
    Write a function `int is_prime(int n)` that returns 1 if n is prime,
    0 otherwise.

    In main():
      - Ask user for an integer n (>= 2)
      - If invalid, print an error
      - Otherwise, print all prime numbers up to n
*/

int is_prime(int n) {
    if (n < 2) {
        return 0;                   /* 0, 1 and negatives are not prime */
    }

    /* Try every divisor d while d * d <= n, i.e. d <= sqrt(n).
       If n had a divisor bigger than sqrt(n), it would also have
       a matching one smaller than sqrt(n), so we would find that first. */
    for (int d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            return 0;               /* found a divisor, so not prime */
        }
    }

    return 1;
}

int main(void) {
    int n;

    printf("Enter an integer n (>= 2): ");
    if (scanf("%d", &n) != 1) {
        printf("Input error: please type a whole number.\n");
        return 1;
    }

    if (n < 2) {
        printf("Error: n must be at least 2.\n");
        return 1;
    }

    printf("Primes up to %d:\n", n);
    for (int k = 2; k <= n; k++) {
        if (is_prime(k)) {
            printf("%d ", k);
        }
    }
    printf("\n");

    return 0;
}
