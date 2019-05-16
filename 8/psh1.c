#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>

#define MAXARGS 20
#define ARGLEN  100

char* makestring(char*);
int execute(char *arglist[]);
int main()
{
	char *arglist[MAXARGS+1];
	int numargs = 0;
	char argbuf[ARGLEN];
	
	while(numargs<MAXARGS){
		printf("Arg[%d]:",numargs);	
		if(fgets(argbuf, ARGLEN, stdin) && (*argbuf)!='\n'){
			arglist[numargs++] = makestring(argbuf);
		} else {
			if(numargs > 0){
				arglist[numargs] = NULL;
				execute(arglist);
				numargs=0;
			}
		}
	}
		
	exit(0);
}
int execute(char *arglist[])
{
	execvp(arglist[0], arglist);
	return 0;
}
char* makestring(char *buf)
{
	char *cp;
	
	buf[strlen(buf)-1] = '\0';
	cp = (char*)malloc(strlen(buf)+1);
	if( NULL == cp){
		fprintf(stderr, "No memary\n");
		exit(1);
	}
	strcpy(cp, buf);
	return cp;
}
