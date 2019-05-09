#include<stdio.h>
#include<curses.h>
#include<signal.h>
#include<string.h>

#define MESSAGE "hello"
#define BLANK   "     "

int row;
int col;
int dir;
void set_ticker(int);
void move_msg(int);	//handler function
int main()
{
	int delay;
	int ndelay;
	int c;		//user input
	
	initscr();
	crmode();
	noecho();
	clear();

	row = 10;	//start here
	col = 0;
	dir = +1;	
	delay = 200;	
	
	move(row, col);
	addstr(MESSAGE);
	signal(SIGALRM, move_msg);	//timer control view
	set_ticker(delay);	
	while(1){
		ndelay = 0;
		c = getch();
		if(c == 'q') break;
		if(c == ' ') dir = -dir;
		if(c == 'f' && delay > 2) ndelay = delay/2;
		if(c == 's') ndelay = delay*2;
		if(ndelay > 0){
			delay = ndelay;
			set_ticker(delay);
		}
	}
	endwin();
	return 0;
}
void move_msg(int signum)
{
	signal(SIGALRM, move_msg);
	move(row, col);		//clear first 
	addstr(BLANK);

	col+=dir;		//make lastest
	move(row, col);
	addstr(MESSAGE);
	
	refresh();
	
	if(dir == -1 && col <= 0)
		dir = 1;
	else if(dir == 1 && col + strlen(MESSAGE) >= COLS)
		dir = -1;
}





