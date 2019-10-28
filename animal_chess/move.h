#ifndef _MOVE_H_
#define _MOVE_H_

#include "common.h"

int get_coords(char piece, State *state, Coord coords[]);
void find_mov_case(char piece, int x, int y, State state, State next_state[], int *num);
void find_pla_case(char piece, State state, State next_state[], int *num);
void get_next_state(char piece, State *state, State next_state[], int *num);
int get_all_next_states(State *state, State next_state[]);
int checkmate(State *state);
int evaluation(State *state);
int strategy(State *state, State next_state[]);
int minimax(State state, int depth, int from);

#endif

