#include <stdio.h>

int main() {
    int user_id;
    int token;

    printf("Enter User ID: ");
    scanf("%d", &user_id);

    printf("Enter Token: ");
    scanf("%d", &token);

    printf("\nCaptured Packet:\n");
    printf("User_ID = %d\n", user_id);
    printf("Token   = %d\n", token);

    printf("\nReplaying the same packet to server...\n");
    printf("Login Successful (Replay Attack)\n");

    return 0;
}
