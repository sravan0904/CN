#include <stdio.h>

int main() {
    int bucket_size, output_rate, incoming_packet, current_level = 0;
    char ch;

    printf("Enter bucket size (capacity): ");
    scanf("%d", &bucket_size);
    printf("Enter output rate (leak rate per cycle): ");
    scanf("%d", &output_rate);

    do {
        printf("\nEnter incoming packet size: ");
        scanf("%d", &incoming_packet);

        if (incoming_packet > bucket_size) {
            printf("Packet size exceeds bucket capacity. Packet dropped.\n");
        } else {
            if (current_level + incoming_packet <= bucket_size) {
                current_level += incoming_packet;
                printf("Packet added to bucket. Current bucket level: %d\n", current_level);
            } else {
                printf("Bucket overflow. Packet dropped.\n");
            }
        }

        // Leak packets at output rate
        if (current_level < output_rate) {
            printf("Bucket leaking all remaining packets: %d\n", current_level);
            current_level = 0;
        } else {
            current_level -= output_rate;
            printf("Bucket leaking packets at output rate. Remaining bucket level: %d\n", current_level);
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &ch);

    } while (ch == 'y' || ch == 'Y');

    return 0;
}
