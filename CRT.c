#include <stdio.h>

// Extended Euclidean Algorithm
int extendedGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Chinese Remainder Theorem Function
int chineseRemainder(int a[], int n[], int size) {
    int N = 1;
    for (int i = 0; i < size; i++)
        N *= n[i];

    int result = 0;

    for (int i = 0; i < size; i++) {
        int Ni = N / n[i];
        int x, y;
        extendedGCD(Ni, n[i], &x, &y);
        x = (x % n[i] + n[i]) % n[i];
        result += a[i] * x * Ni;
    }
    return result % N;
}

int main() {
    int a[] = {2, 3, 1};  
    int n[] = {3, 4, 5};   // m
    int size = 3;

    int x = chineseRemainder(a, n, size);
    printf("Solution x = %d\n", x);
    return 0;
}
