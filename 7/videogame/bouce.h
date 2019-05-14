/*set for game*/
#define BLANK      " "
#define DFL_SYMBOL "o"
#define TOP_ROW 5
#define BOT_ROW 20
#define LEFT_EDGE  10
#define RIGHT_EDGE 70
#define X_INIT 15 /*starting col*/
#define Y_INIT 15 /*starting row*/
#define TICKS_PER_SEC 50

#define X_TTM 5
#define Y_TTM 8

#define FLAP_LENGTH 4
struct ppball{
	int y_pos, x_pos;
	int y_ttm, x_ttm;  /*next count */
	int y_ttg, x_ttg;  /* now count*/
	int y_dir, x_dir;
	char symbol;
};

struct flap{
	int lengths/* = *FLAP_LENGTH*/;
	int pos/* = TOP_ROW+1*/;
};
