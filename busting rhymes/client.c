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
int gameplay(int socket){
	char buffer[256];
	char current_letter[256], *correct[256], *incorrect[256];
	int n=0;
	int x=20;
	int cor = 0, incor =0;
	
	bzero(buffer,256);
	n=read(socket,buffer,255);
	printf("%s",buffer);
	//printf("you have %i guesses left",x);
	while(x!=0){
		printf(" \nPick a letter: ");
		bzero(buffer,256);
		fgets(buffer,256,stdin);
		buffer[strcspn(buffer, "\r\n")] = 0;
		n=write(socket,buffer,strlen(buffer));//sends letter
		stpcpy(current_letter, buffer);
	
		
		
		bzero(buffer,256);
		n=read(socket,buffer,255);//reads reply
		printf("%s \n",buffer);
		
		
		bzero(buffer,256);
		n=read(socket,buffer,255);//reads reply
		printf("%s \n",buffer);
		
		
		
		if(strcmp(buffer,"win")==0 || strcmp(buffer,"lose")==0){
			x=0;
		}
		bzero(buffer,256);
		n=read(socket,buffer,255);//reads reply
		printf("gueeses left: %i \n",*buffer);
		
		bzero(buffer,256);
		n=read(socket,buffer,255);//reads reply
		printf("letters guessed: %s \n",buffer);
		
	}
	//going back to main menu

	return 1;
}
int play_game(int sock_fd){
	char buffer[256];
	int n=0;
	int x=0;
	bzero(buffer,256);
	n=read(sock_fd,buffer,255);
	
	if(strcmp(buffer,"Disconnected")==0){
		printf("Incorrect details.....Disconnecting");
		return 3;
	}
	printf("%s",buffer);
	printf(" Please enter a number(1-3) -> ");
	bzero(buffer,256);
    fgets(buffer,256,stdin);
	buffer[strcspn(buffer, "\r\n")] = 0;
	while(x==0){
		if(strcmp(buffer,"1")==0){
			x=1;
			n=write(sock_fd,buffer,strlen(buffer));//sends option
			gameplay(sock_fd);
			return 1;
		}
		else if(strcmp(buffer,"2")==0){
			x=1;
			n=write(sock_fd,buffer,strlen(buffer));//sends option
			//takes the amount of reads it needs
			bzero(buffer,256);
			n=read(sock_fd,buffer,255);//reads reply
			printf("amount of users: %i \n",*buffer);
			x=*buffer;
			for(int t=0; t<x; t++){
				printf("============================= \n");
				bzero(buffer,256);
				n=read(sock_fd,buffer,255);//reads username
				printf(" Username: %s \n", buffer);
				
				bzero(buffer,256);
				n=read(sock_fd,buffer,255);//reads games won
				printf(" Games Won: %i \n", *buffer);
				
				bzero(buffer,256);
				n=read(sock_fd,buffer,255);//reads games played
				printf(" Games played: %i \n", *buffer);
				
				printf("============================= \n");
			}
			return 1;
		}
		else if(strcmp(buffer,"3")==0){
			x=1;
			n=write(sock_fd,buffer,strlen(buffer));//sends option
			
			return 3;
		}
		else{
			printf(" Please enter a number BETWEEN 1-3 ->");
			bzero(buffer,256);
			fgets(buffer,256,stdin);
			buffer[strcspn(buffer, "\r\n")] = 0;
		}
	}
	if(n<0){ErrorMessage("Error writing in socket");}
	
	
	return 1;
}




int main(int argc,char *argv[]){
	create_game();
    int sock_fd=0, port=0,n=0;
    char buffer[256];
	char buffer2[256];
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
	printf("awaiting connection.........");
	bzero(buffer,256);
    n=read(sock_fd,buffer,255);
	printf("%s \n", buffer);
    printf("PLEASE ENTER YOUR USERNAME---> ");
    bzero(buffer,256);
    fgets(buffer,256,stdin);
	buffer[strcspn(buffer, "\r\n")] = 0;
	n=write(sock_fd,buffer,strlen(buffer));//sends a username
	
	 
    if(n<0)
        ErrorMessage("Error writing in socket");
    bzero(buffer,256);
    n=read(sock_fd,buffer,255);
	if(n<0)
        ErrorMessage("Error reading socket");
	printf("%s>",buffer);
	
	bzero(buffer,256);
    fgets(buffer,256,stdin);
	buffer[strcspn(buffer, "\r\n")] = 0;
	
	n=write(sock_fd,buffer,strlen(buffer));//sends a password
	
	if(n<0)
        ErrorMessage("Error writing in socket");
	
	while(play_game(sock_fd) !=3);
	
    
	
	
	
    return 0;
}