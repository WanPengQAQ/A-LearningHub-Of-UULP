#include<stdio.h>
#include<unistd.h>

void main()
{
	int my_pid, ret_from_fork;

	my_pid = getpid();
	pritnf("Before:my pid is %d\n", my_pid);
	
	ret_from_fork = fork();
	
	sleep(1);
	printf("After: my pid is %d, fork() said %d\n", getpid(), ret_from_fork);	

}
