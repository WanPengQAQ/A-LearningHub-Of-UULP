#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define BUFSIZE 20

int main()
{
	int len, i, apipe[2];
	char buf[BUFSIZE]; 

	if(pipe(apipe) == -1){
		perror("Could not make pipe");
		exit(1);
	}

	printf("Got a pipe fd = {%d, %d}\n", apipe[0], apipe[1]);

	/*read from stdin, write into pipe, read from pipe*/
	while(fgets(buf, BUFSIZE, stdin)){
		len = strlen(buf);
		if(write(apipe[1], buf, len) != len){
			perror("writing to pipe");
			break;
		}
		for(i = 0; i < len+1; i++)
			buf[i] = 'o';

		len = read(apipe[0], buf, BUFSIZE);
		if(len == -1){
			perror("reading from pipe");
			break;
		}	
		write(1, buf, len);
	}

	return 0;
}
