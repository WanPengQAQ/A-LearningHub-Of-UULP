#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define DELAY 10

void child_code(int);
void parent_code(int);

int main()
{
	int newpid;
	printf("int = %d byte\n", sizeof(int));
	printf("Before: mypid is %d\n", getpid());
	
	newpid = fork();
	if(newpid == 0)
		child_code(DELAY);
	else
		parent_code(newpid);
		

	return 0;
}

void child_code(int delay)
{
	printf("child %d here will sleep for %d seconds\n", getpid(), delay);
	sleep(delay);
	printf("child is done\n");
	exit(17);
}

void parent_code(int childpid)
{
	int wait_rv;
	int child_status;
	int high_8, low_7, bit_1;

	wait_rv = wait(&child_status);
	printf("done waiting for %d. Wait retuende: %d\n",childpid, wait_rv);
	
	high_8 = child_status >> 8;
	low_7  = child_status & 0x007F;
	bit_1  = child_status & 0x0080;
	
	printf("status:exit = %d, sig = %d, core = %d\n", high_8, low_7, bit_1);
}












