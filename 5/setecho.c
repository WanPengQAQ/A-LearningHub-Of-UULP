#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>

int main(int ac, char* av[])
{	
	if(ac == 1){
		printf("less argument\n");
		return 1;
	}	

	struct termios info;
	int result = tcgetattr(STDIN_FILENO, &info);
	if(result == -1){
		printf("failure in tcgetattr\n");
		return 1;
	}
	
	if(av[1][0] == 'y'){
		info.c_lflag |= ECHO;
	} else {
		info.c_lflag &= ~ECHO;
	}	
	
	if( tcsetattr(STDIN_FILENO, TCSANOW, &info) == -1){
		printf("set(tcsetattr failure\n)");
		return 1;
	}
	
	return 0;
}
