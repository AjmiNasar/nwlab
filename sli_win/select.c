#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main() {
    int w, i, f, frames[50];
    printf("Enter window size: ");
    scanf("%d", &w);
    printf("Enter number of frames to transmit: ");
    scanf("%d", &f);
    printf("Enter %d frames: ", f);
    for (i = 0; i < f; i++)
        scanf("%d", &frames[i]);

    bool ack[50] = {false}; // Array to keep track of acknowledgments
    int send_base = 0; // Send base of the window
    int next_frame_to_send = 0; // Next frame to be sent

    srand(time(0)); // Seed the random number generator

    printf("\nWith Selective Repeat ARQ the frames will be sent in the following manner\n\n");
    while (send_base < f) {
        // Send frames within the window
        while (next_frame_to_send < send_base + w && next_frame_to_send < f) {
            printf("Sending frame %d\n", frames[next_frame_to_send]);
            next_frame_to_send++;
        }

        // Simulate receiving acknowledgments
        for (i = send_base; i < next_frame_to_send; i++) {
            if (!ack[i]) {
                // Simulate random acknowledgment failure
                if (rand() % 2 == 0) {
                    ack[i] = true;
                    printf("Acknowledgment received for frame %d\n", frames[i]);
                } else {
                    printf("Acknowledgment not received for frame %d\n", frames[i]);
                }
            }
        }

        // Retransmit frames that were not acknowledged
        for (i = send_base; i < next_frame_to_send; i++) {
            if (!ack[i]) {
                printf("Retransmitting frame %d\n", frames[i]);
                // Simulate successful retransmission
                if (rand() % 2 == 0) {
                    ack[i] = true;
                    printf("Acknowledgment received for retransmitted frame %d\n", frames[i]);
                } else {
                    printf("Acknowledgment not received for retransmitted frame %d\n", frames[i]);
                }
            }
        }

        // Move the send base to the next unacknowledged frame
        while (ack[send_base] && send_base < f) {
            send_base++;
        }
    }

    return 0;
}