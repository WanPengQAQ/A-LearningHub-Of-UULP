#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

#define READ 0
#define WRITE 1

FILE* popen(const char* command, const char* mode)
{
	int pfp[2];
	pid_t  pid;	
	FILE* fp;
	int parent_end, child_end;
	
	if(*mode == 'r'){
		parent_end = READ;
		child_end = WRITE;
	} else if (*mode == 'w'){
		parent_end = WRITE;
		child_end = READ;
	} else {
		return NULL;
	} 

	if(pipe(pfp) == -1){
		return NULL;
	}	
	
	pid = fork();
	if(pid == - 1)
		return NULL;
	if(pid == 0){	//child process
		if(close(pfp[child_end]) == -1)
			exit(1);
		//redirect
		if(dup2(pfp[child_end], child_end) == -1)
			exit(1);
		if(close(pfp[child_end]) == -1)
			exit(1);
		
		execl("/bin/sh","sh","-c",command,NULL);
		exit(1);
		
	} else {		//parent process
		if(close(pfp[child_end]) == -1)
			return NULL;
		return fdopen(pfp[parent_end], mode);
	}
	
}
