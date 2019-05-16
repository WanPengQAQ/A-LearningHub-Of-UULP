#include<stdio.h>
#include<unistd.h>

void main()
{
	int fork_rv;
	fork_rv = fork();
	if(fork_rv == -1)
		perror("fork");
	else if(fork_rv == 0)
		printf("I am child. My pid is %d\n",getpid());
	else
		printf("I am parent. My child is %d\n", fork_rv);
}
