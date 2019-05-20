#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>

int execute(char** arglist)
{
	pid_t pid, child_info;

	if(arglist[0] == NULL) /*nothing to do*/
		return 0;
	
	pid = fork();
	if(pid == -1)
		perror("fork");
	else if(pid == 0){		/*child process*/
		signal(SIGINT, SIG_DFL);	//SIG_IGN in parent process, but child process can be killed by  
		signal(SIGQUIT, SIG_DFL); 
		execvp(arglist[0], arglist);
		
		exit(1);
	} else {				/*parent process*/
		if(wait(&child_info) == -1){
			perror("wait");
		}
		return child_info;
	}
}
