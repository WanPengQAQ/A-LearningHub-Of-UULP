#include<stdio.h>
#include<stdlib.h>

int main()
{
	char* arglist[3];
	
	arglist[0] = "ls";
	arglist[1] = "-l";
	arglist[2] = NULL;

	printf("exectue ls\n");
	execvp("ls", arglist);
	printf("ls is done\n");
}
