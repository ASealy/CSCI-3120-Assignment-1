#include <stdio.h>
#include <unistd.h>
#define MAX_LINE 80

int main(void){

	char args[MAX_LINE/2 + 1];
	int should_run=1;

	while(should_run==1){
		printf("CSCI3120> ");
		fflush(stdout);
		scanf ("%[^\n]%*c", args);
		fflush(stdin);

		if(strcmp(args,"exit")==0){ 
			should_run=0; 
			continue; 
		}
		if(args[0]==' '||args==NULL) continue;


		int i=0;
		int num_commands=1;

		for(i=0;i<MAX_LINE/2+1;i++) if(args[i]==' ') num_commands++;
			printf("Num Commands: %d\n",num_commands);
		fflush(stdout);

		char *p=strtok (args," ");
		char *commands_array[num_commands];

		i=0;
		while (p!=NULL){
			commands_array[i++]=p;
			p=strtok (NULL," ");
		}

		for (i=0;i<num_commands;i++){
			printf("%s\n",commands_array[i]);
			fflush(stdout);
		} 
		

		commands_array[num_commands]=NULL;
		execvp(commands_array[0],commands_array);


		for (i=0;i<num_commands;i++) commands_array[i]=NULL;

	}


return 0;
}