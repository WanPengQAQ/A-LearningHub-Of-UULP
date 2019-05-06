#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>

#define QUESTION "Do you want another transaction"
/*
 * set tty into char-by-char mode, and no buff
 */
	

int get_response(char*);
void set_crmode(); //set stdin into char-by-char and no buffering
void tty_mode(int how);	//how==1, save current mode; how==0, restore mode
int main()
{
	int response;
	tty_mode(1);
	set_crmode();
	response = get_response(QUESTION);
	tty_mode(0);
	return response;
}

int get_response(char* question)
{
	int input;
	printf("%s (y/n)? ", question);
	while(1){
		input=getchar();
		switch(input){
			case 'Y':
			case 'y': printf("\n");return 0;
			case 'N':
			case 'n':
			case EOF: printf("\n");return 1;
			default:
				printf("\n Cannot understand %c ", input);
				printf("please type y or n:");
		}
	}
}

void set_crmode()
{
	struct termios ttystate;
	tcgetattr(STDIN_FILENO, &ttystate);
	ttystate.c_lflag &= ~ ICANON;   //close buff
	ttystate.c_cc[VMIN] = 1; 	//char-by-char
	tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
void tty_mode(int how)
{
	static struct termios original_mode;
	if(how == 1){
		tcgetattr(STDIN_FILENO, &original_mode);
	} else {
		tcsetattr(STDIN_FILENO, TCSANOW, &original_mode);
	}
	
}



