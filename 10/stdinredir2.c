#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define CLOSE_DUP
#define USE_DUP2

int main()
{	
	int fd;
	int newfd;
	char line[100];

	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	
	fd = open("./data", O_RDONLY);
	if(fd == -1){
		printf("open data error\n");
		exit(1);
	}
#ifdef USE_DUP2
	close(0);
	newfd = dup(fd);
	printf("close dup \n");
#else
	newfd = dup(fd, 0);
#endif
	
	if(newfd!=0){
		fprintf(stderr, "Could not duplicate fd to 0\n");
		exit(1);
	}
	close(fd);
	
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);

	return 0;
}
