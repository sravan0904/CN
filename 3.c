#include <stdio.h>
#include <string.h>

// Function to calculate checksum (simple sum of bytes modulo 256)
unsigned char calculateChecksum(char *data) {
    unsigned int sum = 0;
    for (int i = 0; i < strlen(data); i++) {
        sum += data[i];
    }
    return (unsigned char)(sum % 256);
}

void sender(char *data, char *frame) {
    unsigned char checksum = calculateChecksum(data);
    strcpy(frame, data);
    int len = strlen(data);
    frame[len] = checksum;   // Append checksum byte
    frame[len + 1] = '\0';
    printf("Sender sends data with checksum: ");
    for (int i = 0; i < strlen(frame); i++) {
        printf("%c", frame[i]);
    }
    printf("\n");
}

int receiver(char *frame) {
    int len = strlen(frame);
    char data[100];
    strncpy(data, frame, len - 1);
    data[len - 1] = '\0';

    unsigned char receivedChecksum = frame[len - 1];
    unsigned char calculatedChecksum = calculateChecksum(data);

    printf("Receiver calculates checksum: %u\n", calculatedChecksum);
    if (calculatedChecksum == receivedChecksum) {
        printf("Checksum matches. Data is error-free: %s\n", data);
        return 1;
    } else {
        printf("Checksum mismatch! Data corrupted.\n");
        return 0;
    }
}

int main() {
    char data[100], frame[110];
    printf("Enter data to send: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;  // Remove newline character

    sender(data, frame);

    // Simulate receiver checking frame
    receiver(frame);

    return 0;
}
