#include<stdio.h>

int main(int args, char* argv[])
{
	int i;
	printf("Number of args: %d,Args are:\n", args);
	
	for(i=0; i<args; i++)
		printf("args[%d] %s\n", i, argv[i]);
	
	fprintf(stderr, "This message is sent to stderr.\n");	
	return 0;
}
