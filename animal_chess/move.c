#include "move.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int get_coords(char piece, State *state, Coord coords[]) //get state(dead or not) and location of each piece
{
	int i, j;
	int n = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (state->board[i][j] == piece)
			{
				coords[n].x = j;
				coords[n].y = i;
				coords[n].dead = 0;
				n++;
			}
		}
	}
	for (j = 0; j < (int)strlen(state->my_hand); j++)
	{
		if (state->my_hand[j] == piece)
		{
			coords[n].x = -1;
			coords[n].y = -1;
			coords[n].dead = 1;
			n++;
			break;
		}
	}
	return n;
}

void find_mov_case(char piece, int x, int y, State state, State next_state[], int *num) //find next states type 'move'
{
	int nx, ny;
	int i;
	int n = *num;
	int dx[8], dy[8];
	char dead_en;
	int num_moving_case = delta_base(piece, dx, dy);

	for (i = 0; i < num_moving_case; i++)
	{
		nx = x + dx[i];
		ny = y + dy[i];

		if (is_out(nx, ny) || !islower(state.board[ny][nx]))
			continue;

		next_state[n] = state;
		dead_en = next_state[n].board[ny][nx];
		next_state[n].board[y][x] = 'o';
		
		if ((piece == 'C') && (y == 0)) //evolution from chick to hen
			next_state[n].board[ny][nx] = 'H';
		else
			next_state[n].board[ny][nx] = piece;

		if (checkmate(&next_state[n]))
			continue;

		if ((piece == 'L') && (y == 0)) //go to enemy's end board
			next_state[n].point += 256;

		next_state[n].point += point_base(dead_en);
                change_upper_lower(&dead_en);
                my_hand_ctrl(dead_en, next_state[n].my_hand, 1);
                
		n++;
	}

	*num = n;
}
				
void find_pla_case(char piece, State state, State next_state[], int *num) //find next states type 'place'
{
	int i, j;
	int n = *num;

	for (i = 0; i < 4; i++)
        {
        	for (j = 0; j < 3; j++)
                {
                	if (state.board[i][j] != 'o')
				continue;
                        
                        next_state[n] = state;
                        next_state[n].board[i][j] = piece;
				
			if (checkmate(&next_state[n]))
				continue;
                                                
                        my_hand_ctrl(piece, next_state[n].my_hand, 0);
                        
			n++;
		}
	}

	*num = n;
}

void get_next_state(char piece, State *state, State next_state[], int *num) //find all next states of one piece
{
	Coord coords[2];
	int i;
	int n = *num;
	int num_piece = get_coords(piece, state, coords);
		
	for (i = 0; i < num_piece; i++)
	{
		if (coords[i].dead == 0)
			find_mov_case(piece, coords[i].x, coords[i].y, *state, next_state, &n);
		else
			find_pla_case(piece, *state, next_state, &n);
	}
	
	*num = n;
}

int get_all_next_states(State *state, State next_state[])
{
	int num = 0;
	Coord coords[2];

	if (get_coords('L', state, coords) == 0) //if current state has no Lion then return -1
		return -1;

	get_next_state('G', state, next_state, &num);
	get_next_state('E', state, next_state, &num);
	get_next_state('C', state, next_state, &num);
	get_next_state('H', state, next_state, &num);
	get_next_state('L', state, next_state, &num);
	
	return num;
}

int checkmate(State *state)
{
        Coord L_coord[1];

        int threat = 0; //the number of enemies which threaten the lion
        int i, j;
        char en_piece;

        get_coords('L', state, L_coord);

        int Lx = L_coord[0].x;
        int Ly = L_coord[0].y;

        for (i = -1; i <= 1; i++)
        {
                for (j = -1; j <= 1; j++)
                {
                        if (is_out(Lx + i, Ly + j))
                                continue;

                        en_piece = state->board[Ly + j][Lx + i]; //check around the Lion

                        if (en_piece == 'l')
                                threat++;
                        else if ((en_piece == 'g') && (i*j == 0))
                                threat++;
                        else if ((en_piece == 'e') && (i*j != 0))
                                threat++;
                        else if ((en_piece == 'h') && ((i == 0) || (j != 1)))
                                threat++;
                        else if ((en_piece == 'c') && (i == 0) && (j == -1))
                                threat++;
                }
        }

        return threat;
}

int evaluation(State *state) //evaluate the state
{
	State changed_state = *state;
	change_position(&changed_state);
	
	int point = 0;
	int point_my_field = point_of_field(state, 1);
	int point_en_field = point_of_field(state, 0);

	point += (checkmate(&changed_state) * 6); //more my pieces which is threatening the enemy's lion, get more point

	point += (point_my_field - point_en_field); //get more point as more pieces i have

	return point;
}

int strategy(State *state, State next_state[]) //find best choice
{
	int i, max;
	int best[2] = {-1024, 0};
	int num_next_states = get_all_next_states(state, next_state);
	State tmp_state, tmp_next_state[256];

	if (num_next_states == 0) //give up
		return -1;

	for (i = 0; i < num_next_states; i++)
	{
		tmp_state = next_state[i];
		change_position(&tmp_state);
		
		if (get_all_next_states(&tmp_state, tmp_next_state) == 0)
			return i;

		max = minimax(next_state[i], 3, i);

		if (best[0] < max)
		{
			best[0] = max;
			best[1] = i;
		}
	}
			
	return best[1];
}

int minimax(State state, int depth, int from)
{
	int i;
	State next_state[256];
	change_position(&state);
	int n = get_all_next_states(&state, next_state);
	int best = -1024;

    	for (i = 0; i < n; i++)//each child of node
        {	
	        if (depth == 0)
			best = max(best, next_state[i].point + evaluation(&next_state[i]));
		else
			best = max(best, minimax(next_state[i], depth - 1, from));
	}
	
	return -best; //return minus becasue enemy will get this
}

