#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 10

struct frame {
    char ack;
    int data;
} frm[MAX];

int n, r;

// Function prototypes
int sender();
void recvack();
void resend();

void selective() {
    sender();
    recvack();
    resend();
    printf("\nAll packets sent successfully\n");
}

int sender() {
    int i;
    printf("\nEnter the no. of packets to be sent: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter data for packet[%d]: ", i);
        scanf("%d", &frm[i].data);
        frm[i].ack = 'y';
    }
    return 0;
}

void recvack() {
    int lost;
    srand(getpid());
    lost = rand() % n; // Simulate a random lost frame
    frm[lost].ack = 'n';
    for (int i = 0; i < n; i++) {
        if (frm[i].ack == 'n')
            printf("\nPacket number %d is not received\n", i);
    }
    r = lost;
}

void resend() {
    printf("\nResending packet %d...\n", r);
    sleep(2);
    frm[r].ack = 'y';
    printf("The received packet is %d\n", frm[r].data);
}

int main() {
    selective();
    return 0;
}
