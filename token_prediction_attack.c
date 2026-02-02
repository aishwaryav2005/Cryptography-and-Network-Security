#include <stdio.h>
#include <math.h>

int main() {
    int user_id = 2;
    int n = 9;

    printf("Predicting tokens for User_ID = %d\n\n", user_id);

    for (int k = 1; k <= 15; k++) {
        int token = (int)pow(user_id, k) % n;
        printf("k = %2d --> Token = %d\n", k, token);
    }

    printf("\nObservation: Tokens repeat → k is meaningless\n");
    return 0;
}
