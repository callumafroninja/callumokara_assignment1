#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
void ErrorMessage(const char *msg){
    perror(msg);
    return;
}
 
int main(int argc,char *argv[]){
 
    int sock_fd=0,new_sock_fd=0,port=0,clilen=0,n=0;
    char buffer[256];
    struct sockaddr_in serv_addr,cli_addr;
 
    if(argc<2){
        fprintf(stderr,"Error port is missing\n");
        return 0;
    }
 
    sock_fd=socket(AF_INET,SOCK_STREAM,0);
 
    if(sock_fd<0)
        fprintf(stderr,"Error opening socket");
 
    bzero((char *)&serv_addr,sizeof(serv_addr));
    port=atoi(argv[1]);
 
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
 
    if(bind(sock_fd, (struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
        ErrorMessage("Error in connection");
 
    listen(sock_fd,5);
 
    clilen=sizeof(cli_addr);
    new_sock_fd=accept(sock_fd,(struct sockaddr *)&cli_addr,&clilen);
    if(new_sock_fd<0)
        ErrorMessage("Error on accept");
 
    bzero(buffer,256);
    n=read(new_sock_fd,buffer,255);
 
    if(n<0)
        ErrorMessage("Error reading socket");
    printf("Here is the message:%s",buffer);
 
    n=write(new_sock_fd,"Got your message",16);
 
    if(n<0)
        ErrorMessage("Error writing on socket");
    return 0;
}