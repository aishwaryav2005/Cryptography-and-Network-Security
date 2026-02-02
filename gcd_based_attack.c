#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int n = 9;
    int user_id = 3;

    int g = gcd(user_id, n);

    printf("Checking GCD attack\n");
    printf("User_ID = %d, n = %d\n", user_id, n);
    printf("gcd(%d, %d) = %d\n", user_id, n, g);

    if (g > 1) {
        printf("System Broken!\n");
        printf("n = %d x %d\n", g, n / g);
    } else {
        printf("System Safe\n");
    }

    return 0;
}