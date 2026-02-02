#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Modular exponentiation
long long power(long long a, long long d, long long n) {
    long long result = 1;
    a = a % n;
    while (d > 0) {
        if (d % 2 == 1)
            result = (result * a) % n;
        d = d / 2;
        a = (a * a) % n;
    }
    return result;
}

int millerRabin(long long n, int k) {
    if (n <= 1 || n == 4) return 0;
    if (n <= 3) return 1;

    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        long long x = power(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        int composite = 1;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;

            if (x == n - 1) {
                composite = 0;
                break;
            }
        }
        if (composite)
            return 0;
    }
    return 1;
}

int main() {
    long long n = 7919;
    int k = 5;

    srand(time(NULL));

    if (millerRabin(n, k))
        printf("%lld is probably prime\n", n);
    else
        printf("%lld is composite\n", n);

    return 0;
}
