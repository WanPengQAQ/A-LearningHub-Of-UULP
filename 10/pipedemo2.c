#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS   "testing...\n"
#define oops(m,x) {perror(m); exit(x);}
#define BUFSIZE 20

int main()
{
	int pipefd[2];
	int len;
	char buf[BUFSIZE];
	int read_len;
	
	pipe(pipefd);

	switch(fork()){
		case -1:
			oops("cannot fork", 1);	
			break;
		case 0:		//child 
			len = strlen(CHILD_MESS);
			while(1){
				if(write(pipefd[1], CHILD_MESS, len) != len){
					oops("child write", 3);
				}
				sleep(3);
			}
		default:
			len = strlen(PAR_MESS);
			while(1){
				if(write(pipefd[1], PAR_MESS, len) != len)
					oops("parent write", 4);
				sleep(1);
				read_len = read(pipefd[0], buf, BUFSIZE);
				if(read_len <= 0){
					printf("parent exit\n");
					break;
				}
				write(1, buf, read_len);
			}
	}
	return 0;
}
	

