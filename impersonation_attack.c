#include <stdio.h>
#include <math.h>

int main() {
    int fake_user = 4;
    int n = 9;

    printf("Impersonating User_ID = %d\n\n", fake_user);

    for (int k = 1; k <= 6; k++) {
        int token = (int)pow(fake_user, k) % n;
        printf("k = %d --> Token = %d\n", k, token);
    }

    printf("\nAttacker sends: User_ID = 4, Token = 1\n");
    printf("Server accepts for k multiple of 3\n");
    printf("Impersonation Successful\n");

    return 0;
}
