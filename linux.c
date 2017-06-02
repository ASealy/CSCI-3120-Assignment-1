#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_LINE 80

//node object for the history linked list 
typedef struct node {
	//contains value, command string and pointer to next node
	int val;
	char string[MAX_LINE/2 + 1];
	struct node * next;
} node_t;

//function declarations
int size(node_t * head);
void pushfront(node_t ** head, int val, char string[MAX_LINE/2 + 1]);
void print_list(node_t * head);
char *strcpy(char *destination, const char *source);

int main(void){

	//args is the string inputted by the user
	char args[MAX_LINE/2 + 1];
	//should run is 1 if the input is not "exit"
	int should_run=1;
	//first command is 0 if the history is empty, becomes 1 when user enters first command 
	int first_command=0;
	//loop iteration is how many times the user enters a command, used for history counter
	int loop_iteration=1;
	//head of linked list
	node_t * head = NULL;
	head = malloc(sizeof(node_t));

	while(should_run==1){
		//user prompt for input and read into args 
		printf("\n\nCSCI3120> ");
		fflush(stdout);
		scanf ("%[^\n]%*c", args);
		fflush(stdin);

		//different actions actions based on value of input string
		//this will cause the program to exit 
		if(strcmp(args,"exit")==0){ 
			should_run=0; 
			continue; 
		}
		//if nothing is entered, continue
		if(args[0]==' '||args==NULL) continue;
		//this will print the history for the user
		if(strcmp(args,"history")==0) { 
			if(loop_iteration==1){printf("No History.\n"); fflush(stdout);}
			else{print_list(head); continue;} 
		}
		//this will execute the most recent command
		if(strcmp(args,"!!")==0) {
			if(loop_iteration==1){printf("No History.\n"); fflush(stdout);}
			//fetch most recent linked list item and pass below to args 
			else strcpy(args,head->string);
		} 

		//this will find a specific item in the history
		if(args[0]=='!') {

			//the three digits after the ! are parsed into a string
			//this means that history is only supported up to 999 items, but this can be easily expanded
			int digit_one=0,digit_two=0,digit_three=0,search_for=0;
			digit_one=args[1]-48;
			digit_two=args[2]-48;
			if(args[3]!=32)digit_three=args[3]-48;
			else digit_three=-48;	
			int i;	
			for(i=0;i<4;i++) args[i]=0;

			if(digit_one!=-48&&digit_two==-48&&digit_three==-48) search_for=digit_one;
			if(digit_one!=-48&&digit_two!=-48&&digit_three==-48) search_for=digit_one*10+digit_two;
			if(digit_one!=-48&&digit_two!=-48&&digit_three!=-48) search_for=digit_one*100+digit_two*10+digit_three;
			
			//after parsing, the first 10 items in the history are scanned to see if their value is equal to the int from above
			node_t * current = head;
			int search_first_10=0,found=0;
			//only executed 10 times
			while (current != NULL && search_first_10<10) {
				//if the value is found...
				if(current->val==search_for){
					//the string is passed below to args
					strcpy(args,current->string);
					//and found is set to 1
					found=1;
				}
				current = current->next;
				search_first_10++;
			}
			//if found was not set to 1, no such command is in the history
			if(found==0){
				printf("No such command in history...\n");
				fflush(stdout); 
				continue;
			}
			search_first_10=0;
			found=0;
			search_for=0;

		} 
		
		//if this is the first command, a linked list head is initialized
		if(first_command==0){
			first_command=1;
			//the value is set to the loop iteration
			head->val = loop_iteration++;
			//the value of the head is set to the args string from above 
			strcpy(head->string, args);
			head->next = NULL;
			//print_list(head);
			//printf("Size:%d\n",size(*head));

		}
		//if it is not the first command, push it to the front of the list
		else{
			pushfront(&head,loop_iteration++,args); 
			//push(head,loop_iteration++,args); 
			//print_list(head);
			//printf("Size:%d\n",size(*head));
		}
		
		//this parses the args string into an array of strings that is then passed to the execvp function 
		int i=0;
		int num_commands=1;

		for(i=0;i<MAX_LINE/2+1;i++) if(args[i]==' ') num_commands++;

		char *p=strtok (args," ");
		char *commands_array[num_commands];

		i=0;
		while (p!=NULL){
			commands_array[i++]=p;
			p=strtok (NULL," ");
		}

		//Windows testing
		/*
		commands_array[num_commands]=NULL;
		if(strcmp(commands_array[num_commands-1],"&")==0) {printf("Parent must wait\n");fflush(stdout);}
		execvp(commands_array[0],commands_array);


		for (i=0;i<num_commands;i++) commands_array[i]=NULL;
		*/



		int should_wait=0;
		commands_array[num_commands]=NULL;
		if(strcmp(commands_array[num_commands-1],"&")==0){
			commands_array[num_commands-1]=NULL;
			should_wait=1;
		}
		pid_t pid=fork();
		if(pid==0){
			commands_array[num_commands]=NULL;
			execvp(commands_array[0],commands_array);
		}

		if(pid>0) if(should_wait==0) wait(NULL);
		
		for (i=0;i<num_commands;i++) commands_array[i]=NULL;
	
		should_wait=0;

	}

return 0;

}

//linkedlist functions
//this will get the size of the history list 
int size(node_t * head) {
	node_t * current = head;
	int count=0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}
//this will print the first 10 items of the list for the history feature
void print_list(node_t * head) {
	node_t * current = head;
	int print10=0;
	while (current != NULL && print10<10) {
		printf("%d  ", current->val);fflush(stdout);
		printf("%s\n", current->string);fflush(stdout);
		current = current->next;
		print10++;
	}
}
//this will add an item to the front of the linkedlist which will be the most recent item
void pushfront(node_t ** head, int val, char string[MAX_LINE/2 + 1]) {
	node_t * new_node;
	new_node = malloc(sizeof(node_t));
	new_node->val = val;
	strcpy(new_node->string,string);
	new_node->next = *head;
	*head = new_node;
}
