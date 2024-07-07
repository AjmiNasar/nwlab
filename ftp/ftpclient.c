#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define max 1000
#define port 6000
#define sa struct sockaddr
void main()
{
struct sockaddr_in servaddr;
int sockfd, count, flen, i;
char buff1[max], buff2[max], pid_str[10];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(port);
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
connect(sockfd, (sa*)&servaddr, sizeof(servaddr));
printf("\nEnter the filename:\n");
count = read(0, buff1, max);
buff1[count - 1] = '\0';
write(sockfd, buff1, count);
flen = read(sockfd, buff2, max);
if (flen == 0)
printf("\nFile not present....!!!");
else
{
printf("\nPrinting content of file:\n");
for (i = 0; i < flen; i++)
printf("%c", buff2[i]);
printf("\n");
read(sockfd, pid_str, sizeof(pid_str));
printf("Received process ID from server: %s\n", pid_str);
}
close(sockfd);
}

