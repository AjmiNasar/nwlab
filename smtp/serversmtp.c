

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

void recvmail(){

struct sockaddr_in server;

int sockfd,len;

char buff[MAX];

sockfd=socket(AF_INET,SOCK_DGRAM,0);

if(sockfd==-1){

printf("socket creation failed");

exit(0);

}

else

   printf("socket created successfully\n");

   

server.sin_family=AF_INET;

server.sin_addr.s_addr=htonl(INADDR_ANY);

server.sin_port=htons(PORT);

if((bind(sockfd,(SA*)&server,sizeof(server)))!=0){

printf("binding failed");

}

else{

printf("binding successful\n");

}

FILE *file=fopen("emailfile.txt","a");

if(file==NULL){

  printf("error in opening the file\n");

  exit(0);

}

printf("waiting for the mail\n");

len=sizeof(server);

recvfrom(sockfd,buff,MAX,0,(SA *)&server,&len);

fprintf(file,"RECEIVED MAIL : %s\n\n  ",buff);

printf("Received mail: %s\t",buff);

recvfrom(sockfd,buff,MAX,0,(SA *)&server,&len);

fprintf(file,buff);

recvfrom(sockfd,buff,MAX,0,(SA *)&server,&len);

fprintf(file,buff);

printf(buff);

 fclose(file);

 close(sockfd);

   

}

int main(){

recvmail();

return 0;

}





