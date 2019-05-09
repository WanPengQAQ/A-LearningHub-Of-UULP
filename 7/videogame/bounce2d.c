#include<curses.h>
#include<signal.h>
#include"bouce.h"

struct ppball the_ball;

void set_up();		//init game
void wrap_up();
void set_ticker(int);
void ball_move(int);	//SIGALRM handler

int main()
{
	int c;
	set_up();
		
	while(1){
		while((c = getch())!='q'){
			if(c == 'f') the_ball.x_ttm--;
			else if(c == 's') the_ball.x_ttm++;
			else if(c == 'F') the_ball.y_ttm--;
			else if(c == 'S') the_ball.y_ttm++;
		}
	}
	wrap_up();
}
void wrap_up()
{
	set_ticker(0);	/*close timer*/
	endwin();
}
void set_up()
{
	the_ball.y_pos = Y_INIT;
	the_ball.x_pos = X_INIT;
	
	the_ball.y_ttm = the_ball.y_ttg = Y_TTM;
	the_ball.x_ttm = the_ball.x_ttg = X_TTM;
	
	the_ball.y_dir = +1;
	the_ball.x_dir = +1;

	//the_ball.symbol = 'o';

	initscr();
	noecho();
	crmode();
	
	signal(SIGINT, SIG_IGN);
	move(the_ball.y_pos, the_ball.x_pos);
	addstr(DFL_SYMBOL);
	refresh();

	signal(SIGALRM, ball_move);
	set_ticker(1000/TICKS_PER_SEC);
}
int bounce_or_lose(struct ppball*bp) /*boundry judge, not finish*/
{
	if(bp->y_pos >= TOP_ROW){
		bp->y_pos = TOP_ROW;
		bp->y_dir = -bp->y_dir;
	}
	if(bp->y_pos <= BOT_ROW){
		bp->y_pos = BOT_ROW;
		bp->y_dir = -bp->y_dir;
	}
	if(bp->x_pos >= RIGHT_EDGE){
		bp->x_pos = RIGHT_EDGE;
		bp->x_dir = -bp->x_dir;
	}
	if(bp->x_pos <= LEFT_EDGE){
		bp->x_pos = LEFT_EDGE;
		bp->x_dir = -bp->x_dir;
	}
	
}
void ball_move(int signum)
{	
	int y_cur, x_cur, moved;
	
	signal(SIGALRM, SIG_IGN);	/*reject interrupt by itself*/
 	y_cur = the_ball.y_pos;
	x_cur = the_ball.x_pos;		/*record currently state*/
	moved = 0;

	the_ball.y_ttg--;
	if(the_ball.y_ttg == 1 && the_ball.y_ttm > 0){ /*col*/
		the_ball.y_ttg = the_ball.y_ttm;
		the_ball.y_pos += the_ball.y_dir;
		moved = 1;
	}
	
	the_ball.x_ttg--;
	if(the_ball.x_ttg == 1 && the_ball.x_ttm > 0){ /*row*/
		the_ball.x_ttg = the_ball.y_ttm;
		the_ball.x_pos += the_ball.x_dir;
		moved = 1;
	}	

	if(moved == 1){
		move(y_cur, x_cur);
		addstr(BLANK);
		//mvaddch(y_cur, x_cur, BLANK);	
		move(the_ball.y_pos, the_ball.x_pos);
		addstr(DFL_SYMBOL);
		bounce_or_lose(&the_ball);	/*boundry judge*/
		move(LINES-1, COLS-1);
		refresh();
	}
	signal(SIGALRM, ball_move);	/*this is aunreliable signal system!!!*/
}
















