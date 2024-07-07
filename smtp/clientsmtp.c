
#include<stdio.h>

#include<stdlib.h>

#include<sys/types.h>

#include<sys/socket.h>

#include<netdb.h>

#include<netinet/in.h>

#include<string.h>

#define MAX 1024

#define PORT 8080

#define SA struct sockaddr

void sendmail(){

struct sockaddr_in server;

int sockfd,len=sizeof(server);

char buff[MAX];

sockfd=socket(AF_INET,SOCK_DGRAM,0);

if(sockfd==-1){

printf("socket creation failed");

exit(0);

}

else

   printf("socket created successfully\n");

   

server.sin_family=AF_INET;

server.sin_addr.s_addr=inet_addr("127.0.0.1");

server.sin_port=htons(PORT);

printf("enter the mail: \n");

fgets(buff,MAX,stdin);

sendto(sockfd,buff,sizeof(buff),0,(SA *)&server,len);

printf("enter CC: ");

fgets(buff,MAX,stdin);

sendto(sockfd,buff,sizeof(buff),0,(SA *)&server,len);

printf("enter the Subject: \n");

fgets(buff,MAX,stdin);

sendto(sockfd,buff,sizeof(buff),0,(SA *)&server,len);

printf("Mail send");

 close(sockfd);

}

int main() {

sendmail();

return 0;

}
