#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


struct list {
char *string;
struct list *next;
};

typedef struct list LIST;
 
void ErrorMessage(const char *msg){
    perror(msg);
    return;
}
 

int opentext(char *username, char *password){
    FILE *ptr_file;
	//int x;
	char buf[1000];
	char *token;
	LIST *current, *head;
	head = current = NULL;
	ptr_file =fopen("Authentication.txt", "r"); //opening a file to check authentification users and passwords
		if (!ptr_file){
			return 1;
		}
	while (fgets(buf,1000, ptr_file)!=NULL){
        		//puts into list
			LIST *node = malloc(sizeof(LIST));
			node->string = strdup(buf);
			node->next = NULL;
			
			if(head ==NULL){
				current = head = node;
			} else{
				current = current->next = node;
			}
	}
	fclose(ptr_file);
	
	for(current=head; current; current=current->next){
		printf("%s", current->string);
		/* get the first token */
	   token = strtok(current->string, " \t");
	   printf( "%s\n", token);
	   printf( "%s\n", username);
	   /* walk through other tokens */
	   
		  //printf( " %s\n", token);
		  if(*token==*username){
			  token = strtok(NULL, "\t");
			  printf( " it works2!\n");
			  if(*token==*password){
				  printf( "password accepted");
				  return 2;
			  }
		  }
		
		  
	   
		
	}
	
	printf( "You entered either an incorrect username or password - disconnecting");
	/*current = head;
	
	printf("%s", current->string);*/
	
	
    return 0;
}
int main(int argc,char *argv[]){
	
	
 
    int sock_fd=0,new_sock_fd=0,port=0,clilen=0,n=0;
    char buffer[256];
    struct sockaddr_in serv_addr,cli_addr;
	opentext("Username", "Password");
	
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
 
    n=write(new_sock_fd,"Got your message\n",16);
	
	n=write(new_sock_fd,"whats your password: ",16);
 
    if(n<0)
        ErrorMessage("Error writing on socket");
	//opentext();
    return 0;
}



