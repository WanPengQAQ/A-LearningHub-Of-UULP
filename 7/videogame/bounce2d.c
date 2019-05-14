#include<curses.h>
#include<signal.h>
#include"bouce.h"

struct ppball the_ball;
struct flap the_flap;

void set_up();		//init game
void wrap_up();
void set_ticker(int);
void ball_move(int);	//SIGALRM handler
void flap_move(int how);//active by input

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
			else if(c == '8' || c == '2'){
				//not adding flap boundry judje yet,coming soon...
				flap_move(0);
				if(c == '8') the_flap.pos--; 
				if(c == '2') the_flap.pos++;
				flap_move(1);
			}
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
	int i;
	the_ball.y_pos = Y_INIT;
	the_ball.x_pos = X_INIT;
	
	the_ball.y_ttm = the_ball.y_ttg = Y_TTM;
	the_ball.x_ttm = the_ball.x_ttg = X_TTM;
	
	the_ball.y_dir = +1;
	the_ball.x_dir = +1;

	//the_ball.symbol = 'o';
	
	the_flap.lengths = FLAP_LENGTH;
	the_flap.pos = TOP_ROW+1;	
	
	initscr();
	noecho();
	crmode();
	
	signal(SIGINT, SIG_IGN);
	//show flap
	standout();
	for(i=TOP_ROW+1; i<TOP_ROW+1+FLAP_LENGTH; i++){
		move(i, RIGHT_EDGE);
		addstr(" ");
	}	
	standend();
	
	//show ball
	move(the_ball.y_pos, the_ball.x_pos);
	addstr(DFL_SYMBOL);
	
	//show boundry
	standout();
	for(i=LEFT_EDGE; i<=RIGHT_EDGE; i++){
		move(TOP_ROW, i);
		addstr(" ");
		move(BOT_ROW, i);
		addstr(" ");
	}
	for(i=TOP_ROW; i<=BOT_ROW; i++){
		move(i, LEFT_EDGE);
		addstr(" ");
		//move(i, RIGHT_EDGE);
		//addstr(" ");
	}
	standend();

	refresh();
	
	signal(SIGALRM, ball_move);
	set_ticker(1000/TICKS_PER_SEC);
}
int bounce_or_lose(struct ppball*bp) /*boundry judge, not finish; ok==1,failure==0*/
{
	if(bp->y_pos <= TOP_ROW){
		bp->y_pos = TOP_ROW+1;
		bp->y_dir = -bp->y_dir;
	}
	if(bp->y_pos >= BOT_ROW){	
		bp->y_pos = BOT_ROW-1;
		bp->y_dir = -bp->y_dir;
	}
	if(bp->x_pos >= RIGHT_EDGE){ //flap judge
		bp->x_pos = RIGHT_EDGE-1;
		//bp->x_dir = -bp->x_dir
		if(the_flap.pos<=bp->y_pos && bp->y_pos<=the_flap.pos-1+the_flap.lengths ){
			//bp->x_pos = RIGHT_EDGE-1;	
			bp->x_dir = -bp->x_dir;
		} else {
			return 0;
		}
	}
	if(bp->x_pos <= LEFT_EDGE){
		bp->x_pos = LEFT_EDGE+1;
		bp->x_dir = -bp->x_dir;
	}
	return 1;
}
void flap_move(int how)	//how == 1,showflap; how == 0,clear
{
	int i;
	for(i=the_flap.pos; i<the_flap.pos+the_flap.lengths; i++){
		move(i, RIGHT_EDGE);
		if(how == 1){standout();addstr(" ");standend(); }
		else if(how == 0) addstr(" ");
	}
	refresh();
}
void ball_move(int signum)
{	
	int y_cur, x_cur, moved;
	
	signal(SIGALRM, SIG_IGN);	/*reject interrupt by itself, but it is unreliable!!*/
 	y_cur = the_ball.y_pos;
	x_cur = the_ball.x_pos;		/*record currently state*/
	moved = 0;

	the_ball.y_ttg--;
	if(the_ball.y_ttg == 0 && the_ball.y_ttm > 0){ /*col*/
		the_ball.y_ttg = the_ball.y_ttm;
		the_ball.y_pos += the_ball.y_dir;
		moved = 1;
	}
	
	the_ball.x_ttg--;
	if(the_ball.x_ttg == 0 && the_ball.x_ttm > 0){ /*row*/
		the_ball.x_ttg = the_ball.y_ttm;
		the_ball.x_pos += the_ball.x_dir;
		moved = 1;
	}	

	if(moved == 1){
		move(y_cur, x_cur);
		addstr(BLANK);
		//mvaddch(y_cur, x_cur, BLANK);	
		if(bounce_or_lose(&the_ball) == 1){
			move(the_ball.y_pos, the_ball.x_pos);
			addstr(DFL_SYMBOL);
		}
		else{
			move(LINES-1, COLS-22);
			addstr("game over");
			set_ticker(0);
		}
		//move(the_ball.y_pos, the_ball.x_pos);
		//addstr(DFL_SYMBOL);
		//bounce_or_lose(&the_ball);	/*boundry judge , THERE IS A BUG!!!!!*/
		move(LINES-1, COLS-1);
		refresh();
	}
	
	signal(SIGALRM, ball_move);	/*this is aunreliable signal system!!!*/
}
















