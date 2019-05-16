#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAXARGS 20
#define ARGLEN  100

char* makestring(char*);
int execute(char* arglist[]);

int main()
{
	char* arglist[MAXARGS + 1];
	int numargs;				/*index of arglist*/
	char argbuf[ARGLEN];
	
	numargs = 0;
	while(numargs < MAXARGS){
		printf("arglist[%d]:", numargs);
		if(fgets(argbuf, ARGLEN, stdin)!=NULL && (*argbuf!='\n')){
			arglist[numargs++] = makestring(argbuf);
		} else {
			if(numargs >0){		 /*numargs==0, just '\n' input; do nothing*/
				arglist[numargs] = NULL;
				execute(arglist);			
				numargs = 0;	/* waiting for another command*/
			}	
		}
	}
	return 0;
}
void child_code(char* arglist[])
{
	int rv;
	rv = execvp(arglist[0], arglist);
	
	if(rv == -1)	/*kill child process*/
		exit(-1);	/*child process running failure*/
	else
		exit(0);	
}
int parent_code()
{
	pid_t wait_rv;
	
	wait_rv = wait(NULL);
	
	if(wait_rv == -1){
		fprintf(stderr, "boom boom boom\n");	
		exit(-1);
	} else {
		return 0; /*parent process success wake up*/
	}
}

int execute(char* arglist[])
{
	pid_t newpid;
	/*creat new process*/
	newpid = fork();

	if(newpid == 0){
		child_code(arglist);
	} else {
		parent_code();	
	}

	return 0;
}

char* makestring(char* buf)
{
	char* cp = NULL;

	buf[strlen(buf)-1] = '\0';
	cp = (char*)malloc(strlen(buf)+1);
	if(cp == NULL){
		fprintf(stderr,"no menory\n");
		exit(1);
	}
	strcpy(cp, buf);
	return cp;
}
