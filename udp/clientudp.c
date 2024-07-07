/*
 Simple udp client
*/

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512 //Max length of buffer
#define PORT 8888 //The port on which to send data

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(void)
{
    struct sockaddr_in si_other;
    int s, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while(1)
    {
        printf("Enter message: ");
        fgets(message, BUFLEN, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character

        // Break the loop if the user enters "exit"
        if (strcmp(message, "exit") == 0)
        {
            break;
        }

        // Send the message
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == -1)
        {
            die("sendto()");
        }

        // Clear the buffer by filling null, it might have previously received data
        memset(buf, '\0', BUFLEN);

        // Try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }

        puts(buf);
    }

    close(s);
    return 0;
}

