#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>

#define INPUTLEN 100

void intHandler(int);
void quitHandler(int);

int main()
{
	char input[INPUTLEN];
	int nchars;

	signal(SIGINT, intHandler);
	signal(SIGQUIT, quitHandler);

	do{
		printf("\nType a message\n");
		nchars = read(STDIN_FILENO, input, INPUTLEN);
		if(nchars == -1)
			perror("read returned an error");
		else {
			input[nchars] = '\0';
			printf("You typed: %s\n", input);
		}
	}while(strncmp(input, "quit", 4));

	return 0;
}
void intHandler(int s)
{
	printf("Received signal %d ..waiting\n", s);
	sleep(2);
	printf("Leaving intHandler\n");
}
void quitHandler(int s)
{
	printf("Received signal %d ..waiting\n",s);
	sleep(3);
	printf("Leaving quitHandler\n");
}
