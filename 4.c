#include <stdio.h>
#include <math.h>
#include <string.h>

// Function to calculate number of parity bits
int calculateParityBits(int m) {
    int r = 0;
    // r should satisfy 2^r >= m + r + 1
    while ((1 << r) < (m + r + 1))
        r++;
    return r;
}

// Function to generate Hamming code
void generateHammingCode(int data[], int m, int hammingCode[]) {
    int r = calculateParityBits(m);
    int n = m + r;  // Total length of hamming code including parity bits

    int j = 0, k = 0;

    // Initialize hamming array with 0
    for (int i = 1; i <= n; i++)
        hammingCode[i] = 0;

    // Place data bits in hamming code array (positions that are not powers of two)
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) != 0) {  // i not power of 2
            hammingCode[i] = data[j];
            j++;
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int parityPos = 1 << i;
        int parity = 0;
        for (int j = 1; j <= n; j++) {
            if (j & parityPos)
                parity ^= hammingCode[j];
        }
        hammingCode[parityPos] = parity;
    }
}

int main() {
    char input[100];
    printf("Enter the binary data bits (e.g. 1011): ");
    scanf("%s", input);

    int m = strlen(input);
    int data[m];
    for (int i = 0; i < m; i++)
        data[i] = input[i] - '0';

    int r = calculateParityBits(m);
    int n = m + r;
    int hammingCode[n + 1];   // 1-based index for ease

    generateHammingCode(data, m, hammingCode);

    printf("Generated Hamming code is: ");
    for (int i = 1; i <= n; i++)
        printf("%d", hammingCode[i]);
    printf("\n");

    return 0;
}
