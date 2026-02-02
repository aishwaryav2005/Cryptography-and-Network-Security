#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Encryption function
void encrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
}

// Decryption function
void decrypt(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - key + 26) % 26 + base;
        }
    }
}

// Brute force attack
void bruteForce(char cipher[]) {
    char temp[100];
    printf("\nBrute Force Attack Results:\n");

    for (int key = 0; key < 26; key++) {
        strcpy(temp, cipher);
        decrypt(temp, key);
        printf("Key %2d : %s\n", key, temp);
    }
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    int key;

    clock_t start, end;
    double time_taken;

    printf("Enter Plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter Key (0-25): ");
    scanf("%d", &key);

    strcpy(ciphertext, plaintext);

    // Encryption
    encrypt(ciphertext, key);
    printf("\nEncrypted Text: %s", ciphertext);

    // Decryption
    decrypt(ciphertext, key);
    printf("Decrypted Text: %s", ciphertext);

    // Brute force with time measurement
    start = clock();
    bruteForce(ciphertext);
    end = clock();

    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken for brute force attack: %f seconds\n", time_taken);

    return 0;
}
