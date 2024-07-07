
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 43454

void func(int connfd)
{
    char buff[MAX];
    int n;
    for (;;)
    {
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));
        printf("From client: %s\t To client: ", buff);
        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in server, client;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if ((bind(sockfd, (struct sockaddr *)&server, sizeof(server))) != 0)
    {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }

    if ((listen(sockfd, 5)) != 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Server listening..\n");
    }
    len = sizeof(client);

    while (1)
    {
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if (connfd < 0)
        {
            perror("Server accept failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Server accepted the client...\n");

            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client.sin_addr, client_ip, INET_ADDRSTRLEN);
            int client_port = ntohs(client.sin_port);
            printf("\nClient IP: %s, Client Port: %d\n", client_ip, client_port);
        }

        if (fork() == 0)
        {
            close(sockfd);
            func(connfd);
            close(connfd);
            exit(0);
        }
        else
        {
            close(connfd);
        }
    }

    close(sockfd);
    return 0;
}


