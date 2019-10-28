#ifndef _COMMON_H_
#define _COMMON_H_

typedef struct {
	char board[4][3];
	char my_hand[10];
	char en_hand[10];
	int point;
} State;

typedef struct {
	int x;
	int y;
	int dead;
} Coord;

void read_game(State *state);
void print_mov(State *state, State *next_state);
int is_out(int x, int y);
int delta_base(char piece, int dx[], int dy[]);
int point_base(char piece);
void my_hand_ctrl(char piece, char my_hand[], int type);
void change_upper_lower(char *piece);
void change_position(State *state);
void clear_str(char string[]);
int point_of_field(State *state, int type);
int max(int a, int b);

#endif
