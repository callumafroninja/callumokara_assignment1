#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
 
void ErrorMessage(const char *msg){
    perror(msg);
    exit(1);
}
 
 
 
 void create_game(){
	
	printf("======================================\n\n");
	
	printf("WELCOME TO THE ONLINE HANGMAN GAMING SYSTEM\n\n");
	
	printf("======================================\n\n");
	
	
	
	
}
int main(int argc,char *argv[]){
	create_game();
    int sock_fd=0, port=0,n=0;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct hostent *server;
 
    if(argc!=3){
        fprintf(stderr,"Syntax: %s hostname port",argv[0]);
        return 0;
    }
 
    port=atoi(argv[2]);
    sock_fd=socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd<0)
        ErrorMessage("Error opening socket");
 
    server=gethostbyname(argv[1]);
    if(server==NULL){
        fprintf(stderr,"Host doesn't exist\n");
        return 0;
    }
 
    bzero((char *)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port=htons(port);
   
    if (connect(sock_fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        ErrorMessage("Error in connection");
 
    printf("PLEASE ENTER YOUR USERNAME-- -> \n");
    bzero(buffer,256);
    fgets(buffer,256,stdin);
    n=write(sock_fd,buffer,strlen(buffer));
 
	printf("PLEASE ENTER YOUR PASSWORD-- ->  \n");
    bzero(buffer,256);
    fgets(buffer,256,stdin);
    n=write(sock_fd,buffer,strlen(buffer));
	
    if(n<0)
        ErrorMessage("Error writing in socket");
    bzero(buffer,256);
    n=read(sock_fd,buffer,255);
 
    if(n<0)
        ErrorMessage("Error reading socket");
    printf("%s\n",buffer);
	
	
	
    return 0;
}