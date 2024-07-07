#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
srand(time(NULL));
   
   int nframe;
   printf("enter the no of frames : ");
   scanf("%d",&nframe);
   int cur_pack = 1;
   int ack;

   
while (cur_pack <= nframe)
    {
       
        printf("\nSender sent packet %d \n", cur_pack);

        // Simulate packet transmission (with probability of 25% loss)
        if (rand() % 4 != 0) //receive packet
        {
            printf("Receiver received %d\n", cur_pack);
                printf("Receiver sends ack for packet %d\n",cur_pack);
            ack = 1;
        }
        else //packet lost
        {
          ack = 0;
            printf("Packet %d is lost.\n", cur_pack);
        }

        // Check if ACK received (with probability of 25% loss)
        if (ack)
        {
            if (rand() % 4 != 0)
            {
                // Sender receives ACK
                printf("Sender received ACK for packet %d.\n", cur_pack);
cur_pack++;
               
            }
            else
            {
                // Simulate ACK loss
                printf("ACK lost.\n");
            }
        }

    }

    return 0;
}
