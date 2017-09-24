#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Callum and Okara n9170324 QUT 
struct list {
char *string;
struct list *next;
};

typedef struct list LIST;
 
void ErrorMessage(const char *msg){
    perror(msg);
    return;
}
 

/*int opentext(char *username, char *password, int sock){
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
		/* get the first token 
	   token = strtok(current->string, " \t");
	  // token2 = strtok(current->next->string, " \t");
	   
	   printf( "%s\n", token);
	  // printf( "%s\n", username);
	   /* walk through other tokens 
	   
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
	
	printf("%s", current->string);
	
	
    return 0;
}*/

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
	int z = 0;
	char *words_total[1000];
	//stuff for random and word
	int n;
	time_t t;
	srand((unsigned) time(&t));
	printf(" seeds the random bitch\n");
	
	
	
    char *p = strtok (array1, " ,\n\r");
    char *array[array_length];//[array_length];
	
	
   while (p != NULL)
    {
		
			array[i++] = p;
			p = strtok (NULL, " ,\n\r");
			z = 1;
		
		
    }
	n = rand() % 50; //hardcode it now
	printf("%d\n", array_length);
	printf("%d\n", n);
	printf("%s\n", array[1]);
	printf("%s\n", array[2]);
	printf("%s\n", array[3]);
    
	if(n%2 == 0){
		printf(" even");
		words_total[0] = array[n];
		words_total[1] = array[n+1];
		
	}
	else if(n%2==1){
		printf(" odd");
		words_total[0] = array[n-1];
		words_total[1] = array[n];
		//printf(" assigns the random bitch3");
		
	}
	else{
		printf(" neither");
		words_total[0] = array[n];
		words_total[1] = array[n+1];
		//printf(" assigns the random bitch4");
		
	}
	
	
    return *words_total;
	
}

/*char* chosen_word(char* tokenised_list, int array_length){
	
	//randomly selects chosen word to send back to game
	int i, n;
	time_t t;
	
	char *word1[1000]; 
	char *word2[1000];
	char *words_total[1000];
	 /* Intializes random number generator 
    srand((unsigned) time(&t));
	printf(" seeds the random bitch\n");
	n = rand() % array_length;
	i = n+1;
	printf(" assigns the random bitch\n");
	if(n == 0){
		word1[0] = &(tokenised_list[n]);
		//words[1] = tokenised_list[n+1];
		printf(" assigns the random bitch2");
	}
	else{
		word1[0] = &(tokenised_list[n]);
		word2[0] = &(tokenised_list[i]);
		printf(" assigns the random bitch4 %s %s", &(tokenised_list[0]), &(tokenised_list[19]));
	}
	/*else if(n % 2 == 0){
		words[0] = tokenised_list[n];
		words[1] = tokenised_list[n+1];
		printf(" assigns the random bitch3");
	}
	else if(n % 2 == 1){
		words[0] = tokenised_list[n-1];
		words[1] = tokenised_list[n];
		printf(" assigns the random bitch4");
	}
	
	
	return *word1;
}*/


/*int playgame(int sock){
	 char *words = ReadFile("hangman_text.txt");
	 char *tokens;
	 char *chosenword, placeholderz[10];
	 int string_length = strlen(words), n=0;
	 int len, placeholder;
	 int counter=20;
	 char user_input[1];
	 

   
	 
	 tokens = tokenise(words, string_length);
	 len = strlen(tokens);
	 placeholder = len;
	 printf(" words are tokenised print token 1 : %s %s \n", &(tokens[0]), &(tokens[len+1]));
	 printf(" The current word: ");
	 printf("if statement works? %d", len);
	for(int b=0; b<len; b++){
		  printf("_");
		 
	 }
	 printf("if statement works? %d", len);
	 printf(" ");
	 for(int c=0; c<len; c++){
		  printf("_");
		 
	 }
	 printf("if statement works? %d", placeholder);
	 
	printf( "\n Enter a value :");
	scanf("%s",&user_input);
	//placeholderz = tokens[0];
	strcpy(placeholderz, tokens);
	
	char line[1024];
	printf("%s\n", &(placeholderz[0]));
	scanf("%1023[^\n]", line);
	printf("%s\n", line);
	//gets(user_input);
	if(counter==0){
		printf( "YOU HAVE FAILED");
		
	}else if(counter>0){
		
		printf("if statement placeholder? %d", placeholder);
    
		//printf("if statement len? %s", &(placeholderz[0]));
		printf("Word so far: ");
	
	//case if token[0] has any matches then add them
	for(int z=0; tokens[z] != '\0'; z++){
		  if(user_input==&(placeholderz[z])){
			 printf("%s", user_input);
		  }
		 else{
			 printf("_");
			 counter--;
		 }
		 //printf("%s", &(tokens[z]));
		 // printf(" compares %s  ", user_input);
	 }
	//else counter--
	
	}
    printf( "\nYou entered: ");
    //puts(user_input);
	
	
	 //chosenword= chosen_word(tokens, string_length);
	 //printf(" the chosen one is: %s %s", &(chosenword[0]), &(chosenword[1]));
	 n=write(sock, " your chosen word is: ",30);
	 
	/* for(int i=0; i<string_length; i++){
	   printf("%c ", words[i]);
   }//it fucking works
	
}*/
int gameplay(char *word, char *word_2, int socket){
	int n=0;
	int tries = 20;
	int safety = 0;
	char buffer[1000];
	int placeholder[30];
	int increment=0; 
	int placeholder2[30];
	int increment2=0;
	char *ret;
	printf(" char first word: %c, second word %s \n",word[0],word_2);
	n=write(socket,"Words: _______ _______ \n",40);
	
	//new set
	char *first_word;
	/*for(int v=0; v<strlen(word); v++){
		first_word[v] = word[v];
	}*/
	
	//end new set
	//ret = strstr(word, "z");
	//printf("The substring is: %s\n", ret);
	int r = 0; //r is the placeholder to put points etc...
	int q=0;
	while(tries!=0){
		bzero(buffer,256);
		n=read(socket,buffer,255);//reads letter from client
		
		//printf("letter returned %s.%s \n", buffer, &word[0]);
		//first word
			if(strstr(word, buffer)!=0){
				
				safety=1;
				//placeholder[increment]=r;
				increment++;
				printf("first word has a match!\n");
				
				if(strstr(word_2, buffer)!=0){
				
				printf("Second word has a match!\n");
				increment2++;
				}
				
			}
			else{
				if(strstr(word_2, buffer)!=0){
				safety=1;
				printf("Second word has a match!\n");
				increment2++;
				}
				else{
				safety =0;	
				}
				
			}
		//second word
			
		
		if(safety==0){
			tries--;
			n=write(socket,"letter not found \n",40);
			
		}
		else{
			safety = 0;
			n=write(socket,"wrong words \n",40);
		}
		
		}
}

int playgame(int socket){
	//variables 
	int string_length = 10000;
	int x=0, n=0;
	char *p;
    char *array[string_length];
	time_t t;
	char test[20];
	char test2[20];
	//opens file
	FILE *file;
    char buffa[1000];
    file =fopen("hangman_text.txt","r");	
		if (!file){
        		return 1;
		}
	//live validate, tokenises and puts words into array
	while(fgets(buffa,1000, file)!=NULL){
		
		//first word
		p=strtok(buffa, " ,");
		array[x]=malloc(strlen(p) + 1);
		strcpy(array[x],p);
		
		x++;
		
		//association
		p=strtok(NULL, " \t\r\n");
		array[x]=malloc(strlen(p) + 1);
		strcpy(array[x],p);
		
		x++;
	}
	
	fclose(file);
	//end array placement and close file
	
	//start to randomise word selection
	srand((unsigned) time(&t));
	n = rand() % x;
	if(n%2==0){
		printf("chosen words are %s and %s", array[n], array[n+1]);
		strcpy(test,array[n]);
		strcpy(test2,array[n+1]);
	}
	else{
		printf("chosen odd are %s and %s", array[n-1], array[n]);
		strcpy(test,array[n-1]);
		strcpy(test2,array[n]);
	}
	gameplay(test, test2, socket);
	//printf("does it copy? %c",test[0]);
	return 0;
	
}


int validate(char *username, char *password){
	int string_length = 1000;
    int i = 0;
	int z = 0;
    char *p;
    char *array[string_length];
	int x=0;


//new stuff starts
	FILE *file;
    char buffa[1000];
    file =fopen("Authentication.txt","r");	
		if (!file){
        		return 1;
		}
	
	while(fgets(buffa,1000, file)!=NULL){
		
		//username
		p=strtok(buffa, " \t");
		array[x]=malloc(strlen(p) + 1);
		strcpy(array[x],p);
		x++;
		
		//password
		p=strtok(NULL, " \t\r");
		array[x]=malloc(strlen(p) + 1);
		strcpy(array[x],p);
		x++;
	}
	
	fclose(file);
	
//ends	
	
	
  
	
	for(int a=2; a<21;a++){
		
		if(strcmp(array[a],username)==0){
			
				if(strcmp(array[a+1],password)==0){
					
					return 1;
				}
		
	
			
		}
		
	}
    
	
	return 0;
	
}


int options(char *onetwothree, int socket_transfer){
	
	if(strcmp(onetwothree,"1")==0){
			playgame(socket_transfer);
			
			return 1;
		}
		else if(strcmp(onetwothree,"2")==0){
			//display leaderboard
			return 2;
		}
		else if(strcmp(onetwothree,"3")==0){
			//exit
			return 3;
		}
	return 4;
}

int main(int argc,char *argv[]){
	
	
 
    int sock_fd=0,new_sock_fd=0,port=0,clilen=0,n=0,new_sock_fd2=0,sock_fd2=0;
    char buffer[256];
	char username[256];
	char password[256];
    struct sockaddr_in serv_addr,cli_addr;
	int option;
	
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
		//printf("Here is the message:%s",buffer);	//reading and printing message from client(username)
		
		if(n<0){
			ErrorMessage("Error reading socket");
		}

		n=write(new_sock_fd,"PLEASE ENTER PASSWORD --",30);
		
		if(n<0){
			ErrorMessage("Error writing on socket");
		}
		strcpy(username, buffer);
		
		bzero(buffer,256);
		n=read(new_sock_fd,buffer,255);
		
		strcpy(password, buffer);
		
		
	if(validate(username, password)==1){
		n=write(new_sock_fd,"Options\n 1. Play Game \n 2.Leaderboard \n 3. Exit",70);
		bzero(buffer,256);
		n=read(new_sock_fd,buffer,255);
		option = options(buffer,new_sock_fd);
		
	}
	else{
		n=write(new_sock_fd,"I",70);
	}
	
	
    return 0;
}



