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
 

int opentext(char *username, char *password, int sock){
    FILE *ptr_file;
	//int x;
	char buf[1000], buffer[256];
	char *token, *token2;
	int n=0;
	LIST *current, *head;
	head = current = NULL;
	ptr_file =fopen("Authentication.txt", "r"); //opening a file to check authentification users and passwords
		if (!ptr_file){
			return 1;
		}
	printf("opens the file");
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
		//printf("%s", current->string);
		/* get the first token */
	   token = strtok(current->string, " \t");
	  // token2 = strtok(current->next->string, " \t");
	   
	   printf( "%s\n", token);
	  // printf( "%s\n", username);
	   /* walk through other tokens */
	   
		  //printf( " %s\n", token);
		  if(*token==*username){
			  token = strtok(NULL, "\t");
			 printf( " it works2!\n");
			 // write("please enter password: ");
			 printf("seems to stop here?");
			  n=write(sock,"enter pssword: \n",16);
			  printf( " it works3!\n");
			  bzero(buffer,256);
			 printf( " it works4!\n");
			  n=read(sock,buffer,255);
			  printf( " it works5!\n");
			  printf( "%s\n", token2);
			  printf( "%s\n", buffer);
			  //printf(" Here is the messagev2.0: %s",buffer);
				
				if(n<0){
					ErrorMessage("Error writing on socket");
				}
			 // if(*token==*password){
				//  printf( " it workspsswd!\n");
				 
				//  return 2;
			  //}
		  }
		
		  
	   
		
	}
	
	printf( "You entered either an incorrect username or password - disconnecting");
	/*current = head;
	
	printf("%s", current->string);*/
	
	
    return 0;
}

char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

char* tokenise(char* array1, int array_length){
	char *str;
    int i = 0;
	
    char *p = strtok (array1, " ,\n\t");
    char *array[array_length];
	
	printf(" the mkeniser gets this: %s\n", p);
	/*while(p != NULL) {
		printf("%s\n", p);
		p = strtok(NULL, " ,\n");
					}*/
//3564 characters
   while (p != NULL)
    {
		
        array[i++] = p;
        p = strtok (NULL, " ,\n\t");
		printf("%s\n", array[i-1]);
    }

    
    return *array;
	
}

char* chosen_word(char* tokenised_list){
	
	//randomly selects chosen word to send back to game
	return "zoo place";
}


int playgame(int sock){
	 char *words = ReadFile("hangman_text.txt");
	 char *tokens;
	 char *chosenword;
	 int string_length = strlen(words), n=0;
	 
	 tokens = tokenise(words, string_length);
	 chosenword= chosen_word(tokens);
	 
	 n=write(sock, " your chosen word is: ",30);
	 
	/* for(int i=0; i<string_length; i++){
	   printf("%c ", words[i]);
   }//it fucking works*/
	
}


int main(int argc,char *argv[]){
	
	
 
    int sock_fd=0,new_sock_fd=0,port=0,clilen=0,n=0,new_sock_fd2=0,sock_fd2=0;
    char buffer[256];
	char username[256];
	char password[256];
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
 
    if(bind(sock_fd, (struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
        ErrorMessage("Error in connection");
	}
	
		listen(sock_fd,5);
	 
		clilen=sizeof(cli_addr);
		new_sock_fd=accept(sock_fd,(struct sockaddr *)&cli_addr,&clilen);
		if(new_sock_fd<0){
			ErrorMessage("Error on accept");
		}
		bzero(buffer,256);
		n=read(new_sock_fd,buffer,255);
		printf("Here is the message:%s",buffer);	
		printf("will you send the message back?%s", buffer);
		if(n<0){
			ErrorMessage("Error reading socket");
		}
		
		
		//username=buffer; //potential username allocation 
	 
		n=write(new_sock_fd,"Got your message\n",16);
		printf("sent message back%s", buffer);
		if(n<0){
			ErrorMessage("Error writing on socket");
		}
	//opentext(buffer, "Password", new_sock_fd);
	playgame(new_sock_fd);
	//opentext();
    return 0;
}



