#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
/*
 * get input from this terminal, then output to /dev/pst/*
 * 
 * 
 */
#define BUFSIZE 100

int main(int ac, char* av[])
{
	if(ac != 2){
		fprintf(stderr, "usage: write0 ttyname\n");
		exit(1);
	}

	int fd = open(av[1], O_WRONLY);
	if(fd == -1){
		fprintf(stderr, "open %s failure\n", av[1]);
		exit(1);
	}

	char buf[BUFSIZE];
	while(gets(buf) != NULL){
		write(fd, buf, strlen(buf));
	}

	close(fd);
	return 0;
}
