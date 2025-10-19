#include <stdio.h>
#include <string.h>
#define CRC16_POLY "11000000000000101"

void xor(char *divident, char *divisor, int len) {
    for (int i = 0; i < len; i++)
        divident[i] = (divident[i] == divisor[i]) ? '0' : '1';
}

void computeCRC16(char *data) {
    int m = strlen(data);
    int n = strlen(CRC16_POLY);
    char padded, temp;

    strcpy(padded, data);
    for (int i = 0; i < n - 1; i++)
        padded[m + i] = '0';
    padded[m + n - 1] = '\0';

    strncpy(temp, padded, n);
    temp[n] = '\0';

    for (int i = n; i <= m + n - 1; i++) {
        if (temp == '1')
            xor(temp, CRC16_POLY, n);
        memmove(temp, temp + 1, n - 1);
        temp[n - 1] = padded[i];
        temp[n] = '\0';
    }
    printf("CRC-16 checksum: %s\n", temp);
}

int main() {
    char data;
    printf("Enter data bits: ");
    scanf("%s", data);
    computeCRC16(data);
    return 0;
}
