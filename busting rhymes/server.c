#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <pthread.h>

// Callum and Okara n9170324 QUT 
 
struct User {
   char  username[50];
   int   games_played;
   int   games_won;
   int acc_number;
};
struct User bodies[100];
struct User rank[100];
struct User person1;
struct User person2;
struct User person3;
struct User person4;
struct User person5;
struct User person6;
struct User person7;
struct User person8;
struct User person9;
struct User person10; 

int account_number =0; 
int filled =0;
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
	int n=0, word_length_1 = strlen(word), word_length_2 = strlen(word_2);
	int tries = word_length_1 + word_length_2 + 10; //Number of guesses = min{length of word 1 + length of word 2 + 10, 26}
	int safety = 0;
	char buffer[1000], *p;
	char *sendwords[1000];
	char *placeholder[1000];
	int increment=0; 
	char *placeholder2[1000];
	int increment2=0;
	char *ret;
	printf(" length first word: %i, second word %i \n",strlen(word),strlen(word_2));
	n=write(socket,"Words: _______ _______ \n",40);
	
	//new set
	if(tries>26){
		tries = 26;
	}
	char letters_stored[tries];
	
	
	//copying word into new array as chars
	int strlength = strlen(word);
	char charArray[strlength];
	
	for(int i=0; i<strlength; i++){
		charArray[i] = (char) word[i];
		
		
	}
	//copying word2 into new array as chars
	int strlength2 = strlen(word_2);
	char charArray2[strlength2];
	printf(" %i  array length", strlength2);
	for(int i=0; i<strlength2; i++){
		charArray2[i] = (char) word_2[i];
		
		
	}
		
	
	//end new set
	//ret = strstr(word, "z");
	//printf("The substring is: %s\n", ret);
	int r = 0; //r is the placeholder to put points etc...
	int q=0;
	char word_one[strlength];
	
	for(int i=0; i<strlength; i++){
		word_one[i]='_';
	}
	
	char word_two[strlength2];
	
	for(int i=0; i<strlength2; i++){
		word_two[i]='_';
	}
	int wordwin1=1;
	int wordwin2=1;
	int w=0; //placeholder for stored letters
	while(tries!=0){
		
		bzero(buffer,256);
		printf("tries: %i\n", tries);
		
		n=read(socket,buffer,255);//reads letter from client
		wordwin1=1;
		wordwin2=1;
		
		for(int i=0; i<strlength; i++){
			if(word_one[i]=='_'){
				wordwin1=0;
				if(charArray[i]==buffer[0]){
					word_one[i]=charArray[i];
					safety=1;
				}
			}
			else if(word_one[i]==buffer[0]){
				safety=1;
			}
			
		}
		
		for(int i=0; i<strlength2; i++){
			if(word_two[i]=='_'){
				wordwin2=0;
				if(charArray2[i]==buffer[0]){
					word_two[i]=charArray2[i];
					safety=1;
				}
			}
			else if(word_two[i]==buffer[0]){
				safety=1;
			}
		}
		
		letters_stored[w] = buffer[0];
		w++;
		printf("letters so far :%s \n", letters_stored);
		//checks to see if there is a winner!
		wordwin1=1;
		wordwin2=1;
		for(int i=0; i<strlength; i++){
			if(word_one[i]=='_'){
				wordwin1=0;
			}
		}
		for(int i=0; i<strlength2; i++){
			if(word_two[i]=='_'){
				wordwin2=0;
			}
		}
		printf(" it works!! %s %s", word_one, word_two);
		printf(" winner? %i %i", wordwin1, wordwin2);
		if(wordwin1==1 && wordwin2==1){
			printf("you a winner %i", wordwin1);
			n=write(socket,"Well done.....",60);
			sleep(1);
			n=write(socket,"win",60);
			sleep(1);
			n=write(socket,"win",60);
			sleep(1);
			n=write(socket,"win",60);
			printf("obvs get win");
			return 1;
			//sending back to main menu
			
			
			tries =0;//to conclude the while loop
		}
		else{
		
			
		
			if(safety==0){
				tries--;
				printf("does safety go here?");
				sendwords[r] = buffer;
				r++;
				//printf("is it bad here: %s", sendwords);
				if(tries==0){
					n=write(socket,"lose",40);
					sleep(1);
					n=write(socket,"lose",40);
					sleep(1);
					n=write(socket,"lose",40);
					sleep(1);
					n=write(socket,"lose",40);
					
					return 0;
				}
				n=write(socket,word_one,60);
				sleep(1);
				n=write(socket,word_two,60);
				sleep(1);
				n=write(socket,&tries,60);
				sleep(1);
				n=write(socket,letters_stored,60);
			} 
			else{
				safety = 0;
				n=write(socket,word_one,60);
				sleep(1);
				n=write(socket,word_two,60);
				sleep(1);
				n=write(socket,&tries,60);
				sleep(1);
				n=write(socket,letters_stored,60);
				
				//sends both words as they are guessed
				
			}
		}
		
		
		/*if(increment==word_length_1 && increment2==word_length_2){
			printf("you WIN!!!!");
		}*/
		//n=write(socket,word_one,60);
		
		//printf("increment %i, increment2 %i and actual length w1: %i", increment, increment2, word_length_1);
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
	if(gameplay(test, test2, socket)==1){
		printf("gets ti gamplay");
		return 1;
	}
	
	return 0;
	
}


int validate(char *username, char *password){
	int string_length = 1000;
    int i = 0;
	int z = 0;
    char *p;
    char *array[string_length];
	int x=0, place=0;


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
		strcpy(bodies[place].username, p);
		printf("the usernames: %s", bodies[place].username);
		x++;
		place++;
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
			//playgame(socket_transfer);
			
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

void *connection(void *);
void *hold_up(void *);

int main(int argc,char *argv[]){
	/*--- Process client's requests ---*/
	 int sock_fd=0,new_sock_fd=0,port=0,clilen=0,n=0,*new_sock,sock_fd2=0, *new_sock1;
    
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
	

	while(new_sock_fd=accept(sock_fd,(struct sockaddr *)&cli_addr,&clilen)){
		printf("successful connection");
		
		filled++;
		pthread_t child;
		new_sock = malloc(1);
        *new_sock = new_sock_fd;
		/*
			if filled>=10 then create a new thread to pause it whilst it is at that point
		*/
		
		pthread_t child1;
		new_sock1 = malloc(1);
	    *new_sock1 = 1;
	    printf("checks if to que");
		if(filled>=10){
				printf("waittttttt");
				if(pthread_create(&child1, 0, hold_up, (void *) new_sock)<0){
				printf("could not create thread");
				return 1;
				}
			}
		else{
		n=write(new_sock_fd,"successful connection",90);//may clash with other threads?
		}
		printf("connected users: %i \n", filled);
		
		
		if(pthread_create(&child, 0, connection, (void *) new_sock)<0){
			printf("could not create thread");
			return 1;
		}
		printf("handler assigned");
		
	}
if (new_sock_fd < 0)
    {
        printf("accept failed");
        return 1;
    }
    return 0;
//pthread_create(&child, 0, connection(argc, argv), NULL);    /* start thread */
//pthread_detach(child);           /* don't track it */


	//connection(argc, argv);
 
   
    return 0;
}

void *hold_up(void *new_sock_fd1){
	int new_sock_fd = *(int*)new_sock_fd1;
	while(filled>=10){
		//waittttttttttttttt
	}
	write(new_sock_fd,"successful connection",90);
	pthread_exit(NULL);
	return 0;
	
}

void *connection(void *new_sock_fd1){
	
		int new_sock_fd = *(int*)new_sock_fd1;
		int n=0, option, user, g=0;
		char buffer[256];
		char username[256];
		char password[256];
		
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
		
		if(strcmp(username,"Maolin")==0){
			 user=1;
		}
		else if(strcmp(username,"Jason")==0){
			 user=2;
		} 
		else if(strcmp(username,"Mike")==0){
			 user=3;
		} 
		else if(strcmp(username,"Peter")==0){
			 user=4;
		} 
		else if(strcmp(username,"Justin")==0){
			 user=5;
		} 
		else if(strcmp(username,"Anna")==0){
			 user=6;
		} 
		else if(strcmp(username,"Timothy")==0){
			 user=7;
		} 
		else if(strcmp(username,"Anthony")==0){
			 user=8;
		} 
		else if(strcmp(username,"Paul")==0){
			 user=9;
		} 
		else if(strcmp(username,"Richie")==0){
			 user=10;
		} 
		
		  
			 
   
   
		
		
		//strcpy(person1.username, username);
		//printf( "Book 1 title : %s\n", person1.username);
		while(option !=3){//keeps program running until user has decided to exit
		sleep(1);
		n=write(new_sock_fd,"Options\n 1. Play Game \n 2.Leaderboard \n 3. Exit",70);
		bzero(buffer,256);
		n=read(new_sock_fd,buffer,255);
		option = options(buffer,new_sock_fd);
		if(option ==1){
			if(playgame(new_sock_fd)==1){
					printf("game was played");
					bodies[user].games_played++;
					bodies[user].games_won++;
			}
			else{
				bodies[user].games_played++;
			}
			printf("prints?");
			printf("games played: %i",bodies[user].games_played);
		}
		else if(option==2){
			struct User ranking;
			//rank = bodies;
			for(int x=0; x<10; x++){
				rank[x]= bodies[x];//an array to store the rankings 
				
			}
			for(int y=1; y<10; y++){//stores the rankings - generates when leader-board is selected
				for(int z=y+1; z<10; z++){
					if(rank[y].games_won>rank[z].games_won){
						ranking =  rank[y];
						rank[y] = rank[z];
						rank[z] = ranking;
					}
				}
				
			}
			int count=0;
			for(int x=1; x<10; x++){
				printf("order: %s %i \n", rank[x].username, rank[x].games_won);
				if(rank[x].games_won>0){//checks to see games won and whether it should send
					count++;
				}
			}
			n=write(new_sock_fd,&count,60);//sends the amount of users being displayed
			sleep(1);
			
			for(int x=1; x<10; x++){
				if(rank[x].games_won>0){//checks to see games won and whether it should send
					n=write(new_sock_fd,rank[x].username,60);
					sleep(1);
					n=write(new_sock_fd,&rank[x].games_won,60);
					sleep(1);
					n=write(new_sock_fd,&rank[x].games_played,60);
					sleep(1);
				}
			}
		}
		else{
			filled--;//minus the number of users 
		}
		
		}
		account_number++;
	}
	else{
		sleep(1);
		n=write(new_sock_fd,"Disconnected",70);
		bzero(buffer,256);
		/* terminate the thread */
		
		pthread_exit(NULL);
	}
	
	return 0;
}

