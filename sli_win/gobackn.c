#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main() {
    int i, f, w, frames[50];
    printf("Enter window size: ");
    scanf("%d", &w);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    printf("Enter frames: ");
    for (i = 0; i < f; i++) {
        scanf("%d", &frames[i]);
    }

    bool ack[50] = {false};
    int next_frame_to_send = 0;
    int send_base = 0;

    srand(time(0)); // Seed the random number generator

    while (send_base < f) {
        while (next_frame_to_send < send_base + w && next_frame_to_send < f) {
            printf("Sending frame %d\n", frames[next_frame_to_send]);
            next_frame_to_send++;
        }

        for (i = send_base; i < next_frame_to_send; i++) {
            // Simulate random acknowledgment failure
            if (rand() % 2 == 0) {
                ack[i] = true;
                printf("Ack received for %d\n", frames[i]);
            } else {
                printf("Ack not received for %d\n", frames[i]);
                break; // In GBN, stop and retransmit from this frame onward
            }
        }

        // Go-Back-N: retransmit all frames from send_base to next_frame_to_send
        for (i = send_base; i < next_frame_to_send; i++) {
            if (!ack[i]) {
                printf("Retransmitting %d\n", frames[i]);
                next_frame_to_send = i; // Reset to this frame for retransmission
                break;
            }
        }

        // Move the send_base to the first unacknowledged frame
        while (ack[send_base] && send_base < f) {
            send_base++;
        }
    }
    return 0;