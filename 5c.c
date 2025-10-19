#include <stdio.h>
#include <string.h>
#define CCITT_POLY "10001000000100001"

void xor(char *divident, char *divisor, int len) {
    for (int i = 0; i < len; i++)
        divident[i] = (divident[i] == divisor[i]) ? '0' : '1';
}

void computeCCITT(char *data) {
    int m = strlen(data);
    int n = strlen(CCITT_POLY);
    char padded, temp;

    strcpy(padded, data);
    for (int i = 0; i < n - 1; i++)
        padded[m + i] = '0';
    padded[m + n - 1] = '\0';

    strncpy(temp, padded, n);
    temp[n] = '\0';

    for (int i = n; i <= m + n - 1; i++) {
        if (temp == '1')
            xor(temp, CCITT_POLY, n);
        memmove(temp, temp + 1, n - 1);
        temp[n - 1] = padded[i];
        temp[n] = '\0';
    }
    printf("CRC-CCITT checksum: %s\n", temp);
}

int main() {
    char data;
    printf("Enter data bits: ");
    scanf("%s", data);
    computeCCITT(data);
    return 0;
}
