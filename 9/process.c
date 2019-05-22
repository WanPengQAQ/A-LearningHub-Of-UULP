#include<stdio.h>
#include "smsh1.h"

int is_control_command(char*);
int do_control_command(char**);
int ok_to_execute();

int process(char** arg)
{
	int rv = 0;	
	if(arg[0] == NULL)
		rv = 0;
	else if(is_control_command(arg[0]))
		rv = do_control_command(arg);
	else if(ok_to_execute())
		rv = execute(arg);
	return rv;
}
