#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_LINE 80



typedef struct node {
	int val;
	char string[MAX_LINE/2 + 1];
	struct node * next;
} node_t;

int size(node_t * head);
void pushfront(node_t ** head, int val, char string[MAX_LINE/2 + 1]);
void print_list(node_t * head);

int main(void){



	char args[MAX_LINE/2 + 1];
	int should_run=1;
	int first_command=0;
	int loop_iteration=1;
	node_t * head = NULL;
	head = malloc(sizeof(node_t));




//for first call, add the data to head
	//for subsequent calls, call the create function



	while(should_run==1){
		printf("\nCSCI3120> ");
		fflush(stdout);
		scanf ("%[^\n]%*c", args);
		fflush(stdin);

		//actions based on value of input string
		if(strcmp(args,"exit")==0){ 
			should_run=0; 
			continue; 
		}
		if(args[0]==' '||args==NULL) continue;

		if(strcmp(args,"history")==0) { print_list(head); continue; } //print list by item 
		if(strcmp(args,"!!")==0) {//fetch recent list item and pass below

			if(loop_iteration==1) {printf("No History.\n");fflush(stdout);}
			else strcpy(args,head->string);
			//continue;
		} 

		if(args[0]=='!') { //fetch args[1] from list and pass below

			
			node_t * current = head;
			int search_first_10=0,found=0;
			while (current != NULL && search_first_10<10) {
				if(current->val==args[1]-48){ 
					strcpy(args,current->string);
					found=1; 

					//continue;
				}
				current = current->next;
				search_first_10++;
			}
			if(found==0){
				printf("No such command in history...\n");
				fflush(stdout); 
				continue;
			}
			

		} 
		

		if(first_command==0){
			first_command=1;
			head->val = loop_iteration++;
			strcpy(head->string, args);
			head->next = NULL;
			print_list(head);
			//printf("Size:%d\n",size(*head));

		}
		else{
			pushfront(&head,loop_iteration++,args); 
			//push(head,loop_iteration++,args); 
			print_list(head);
			//printf("Size:%d\n",size(*head));
		}
		

		

		


		

		int i=0;
		int num_commands=1;

		for(i=0;i<MAX_LINE/2+1;i++) if(args[i]==' ') num_commands++;
			//printf("Num Commands: %d\n",num_commands);
			//fflush(stdout);

			char *p=strtok (args," ");
		char *commands_array[num_commands];

		i=0;
		while (p!=NULL){
			commands_array[i++]=p;
			p=strtok (NULL," ");
		}

		/*
		for (i=0;i<num_commands;i++){
			printf("%s\n",commands_array[i]);
			fflush(stdout);
		} */
		

		commands_array[num_commands]=NULL;
		if(strcmp(commands_array[num_commands-1],"&")==0) {printf("Parent must wait\n");fflush(stdout);}
		execvp(commands_array[0],commands_array);


		for (i=0;i<num_commands;i++) commands_array[i]=NULL;



		/*
		pid_t pid=fork();
		if(pid==0){
			commands_array[num_commands]=NULL;
			execvp(commands_array[0],commands_array);
		}

		wait(NULL);
		for (i=0;i<num_commands;i++) commands_array[i]=NULL;
		*/


	}




return 0;

}


int size(node_t * head) {
	node_t * current = head;
	int count=0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}



void print_list(node_t * head) {
	node_t * current = head;
	int print10=0;
	while (current != NULL && print10<10) {
		printf("%d - ", current->val);fflush(stdout);
		printf("%s\n", current->string);fflush(stdout);
		current = current->next;
		print10++;
	}
}

void pushfront(node_t ** head, int val, char string[MAX_LINE/2 + 1]) {
	node_t * new_node;
	new_node = malloc(sizeof(node_t));

	new_node->val = val;
	strcpy(new_node->string,string);
	new_node->next = *head;
	*head = new_node;
}