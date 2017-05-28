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
		if(strcmp(args,"!!")==0) { 
		
			if(loop_iteration==1) printf("No History.\n");
			else printf("%s\n",head->string);
			continue;
		} //fetch recent list item and pass below

		if(args[0]=='!') { 

			//printf("%d\n",args[1]-48);
			//printf("\nIndex found? 1 if yes: %d\n",get_index(*head,args[1]-48));
			continue;
		} //fetch args[1] from list and pass below
		

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
			fflush(stdout);

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

int get_index(node_t * head,int index) {
	node_t * current = head;
	while (current != NULL) {
		if(current->val==index) return 1;
		current = current->next;
	}
	return 0;
}

void print_list(node_t * head) {
	node_t * current = head;
	int print10=0;
	while (current != NULL && print10<10) {
		printf("%d - ", current->val);
		printf("%s\n", current->string);
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

void push(node_t * head, int val, char string[MAX_LINE/2 + 1]) {
	node_t * current = head;
	while (current->next != NULL) {
		current = current->next;
	}

    /* now we can add a new variable */
	current->next = malloc(sizeof(node_t));
	current->next->val = val;
	strcpy(current->next->string,string);
	current->next->next = NULL;
}

int remove_last(node_t * head) {
	int retval = 0;
    /* if there is only one item in the list, remove it */
	if (head->next == NULL) {
		retval = head->val;
		free(head);
		return retval;
	}

    /* get to the last node in the list */
	node_t * current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

    /* now current points to the last item of the list, so let's remove current->next */
	retval = current->next->val;
	free(current->next);
	current->next = NULL;
	return retval;

}