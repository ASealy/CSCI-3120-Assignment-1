#include<stdio.h>
#include<unistd.h>
#define MAX_LINE 80

int main(void){

	char args[MAX_LINE/2 + 1];
	int should_run=1;

	while(should_run==1){
		printf("CSCI3120> ");
		fflush(stdout);

		scanf ("%[^\n]%*c", args);
		fflush(stdin);
		if(strcmp(args,"exit")==0) { should_run=0; continue; }
		//printf("Input: %s\n", args);

    //fork child process uning fork()
    //child process will invoke exevp()
    //if command included &, parent will invoke wait()

    //for(int i=0;i<5;i++) if(args[i]!=' ') printf("%c",args[i]);
	//printf("%c\n", args[i]);

		if(args[0]==' '||args==NULL) continue;
		int i = 0;

		int space=-1;
		for(i=0;i<MAX_LINE/2 + 1;i++) if(args[i]==' ') space++;
			printf("%d\n",space);
		fflush(stdout);

		char *p = strtok (args, " ");

		char *array[10];

		i=0;
		while (p != NULL){
			array[i++] = p;
			p = strtok (NULL, " ");
		}

		for (i = 0; i < space; i++){
			printf("%s\n", array[i]);
			fflush(stdout);
		} 
		
		array[space]=NULL;


		execvp(array[0],array);






		for (i = 0; i < space; i++) array[i]=NULL;

			space=-1;

		//now we have each word in array[1..space]



		












		
	}


	return 0;
}