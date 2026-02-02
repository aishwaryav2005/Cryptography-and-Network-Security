#include <stdio.h>
#include <math.h>

int isPrimeTrial(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n = 29;

    if (isPrimeTrial(n))
        printf("%d is prime\n", n);
    else
        printf("%d is not prime\n", n);

    return 0;
}
