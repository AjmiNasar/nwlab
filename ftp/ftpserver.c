 #include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define max 500
#define port 6000
#define sa struct sockaddr
void main()
{
struct sockaddr_in servaddr, cliaddr;
int i, servfd, clifd,count;
int clilen = sizeof(cliaddr), slen = sizeof(servaddr) ,fp;
char buff1[max], buff2[max], pid_str[10];
servfd = socket(AF_INET, SOCK_STREAM, 0);
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(port);
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
bind(servfd, (sa*)&servaddr,slen);
listen(servfd, 5);
clifd = accept(servfd, (sa*)&cliaddr,&clilen);
printf("\nRequest accepted.....\n");
close(servfd);

snprintf(pid_str, sizeof(pid_str), "%d", getpid());
count = read(clifd, buff1, max);
buff1[count] = '\0';
printf("\nFilename is %s", buff1);
if ((fp = open(buff1, O_RDONLY)) >= 0)
{
printf("\nFile opened.....");
count = read(fp, buff2, max);
while (count > 0)
{
printf("\nSending file.....");
write(clifd, buff2, count);
printf("\nPrinting content of file:\n");
for (i = 0; i < count; i++)
{
printf("%c", buff2[i]);
}
printf("\n");
if (i == count)
break;
}
}
else
{
printf("\nRequested file is not present....!!!\n");
write(clifd, "", 1); 
}
close(fp);
write(clifd, pid_str, strlen(pid_str)); 
close(clifd);
}


