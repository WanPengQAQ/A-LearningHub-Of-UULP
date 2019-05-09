/*set for game*/
#define BLANK      " "
#define DFL_SYMBOL "o"
#define TOP_ROW 5
#define BOT_ROW 20
#define LEFT_EDGE  10
#define RIGHT_EDGE 70
#define X_INIT 10 /*starting col*/
#define Y_INIT 10 /*starting row*/
#define TICKS_PER_SEC 50

#define X_TTM 5
#define Y_TTM 8

struct ppball{
	int y_pos, x_pos;
	int y_ttm, x_ttm;  /*next count */
	int y_ttg, x_ttg;  /* now count*/
	int y_dir, x_dir;
	char symbol;
};
