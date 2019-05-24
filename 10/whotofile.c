#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	pid_t pid = fork();
		
	if(pid == 0){//child  stdout->data, 
		close(1);
		creat("userlist",0644);
		execlp("who","who",NULL);	
	
		exit(1);
	} else {	//parent
		wait(NULL);		
		printf("parent over\n");
	}
	


	return 0;
}
