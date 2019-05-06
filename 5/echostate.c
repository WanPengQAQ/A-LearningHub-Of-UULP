#include<stdio.h>
#include<termios.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	struct termios info;
	int rv;

	rv = tcgetattr(STDIN_FILENO, &info);
	if(rv == - 1){
		perror("tcgetattr");
		exit(1);
	}
	if(info.c_lflag & ECHO)
		printf("echo is on\n");
	else
		printf("echo is off\n");
	return 0;
}
