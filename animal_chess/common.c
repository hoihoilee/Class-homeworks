#include "common.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void read_game(State *state)
{
	int i, j;
	char c;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((c = fgetc(stdin)) != '\n') //don't get new line
				state->board[i][j] = c;
		}
	}
	fgets(state->my_hand, sizeof(state->my_hand), stdin);
	state->my_hand[strlen(state->my_hand)-1] = '\0'; //delete new line
	fgets(state->en_hand, sizeof(state->en_hand), stdin);
        state->en_hand[strlen(state->en_hand)-1] = '\0';
	state->point = 0;
}

void print_mov(State *state, State *next_state) //print move with current state and next state
{
	int i, j;
	int x1, x2, y1, y2;
	int n = 0;
	char piece;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (state->board[i][j] == next_state->board[i][j])
				continue;

			if (next_state->board[i][j] != 'o')
			{
				x1 = j; //to
				y1 = i;
				piece = next_state->board[i][j];
				n++;
			}
			else
			{
				x2 = j; //from
				y2 = i;
				n++;
			}
		}
	}
	
	if ((piece != state->board[y2][x2]) && (n == 2)) //evolution from chick to hen
		piece = 'C';

	if (n == 2) //move
		printf("%c %c%d %c%d\n", piece, x2 + 65, y2 + 1, x1 + 65, y1 + 1);
	else //place
		printf("%c P %c%d\n", piece, x1 + 65, y1 + 1);
}

int is_out(int x, int y) //check piece go out from board
{
	if (x < 0 || x > 2 || y < 0 || y > 3)
		return 1;

	return 0;
}

int delta_base(char piece, int dx[], int dy[]) //moving case of each piece
{
        int n;

        switch(piece)
        {
        case 'G' :
        case 'g' :
                dx[0] = -1, dy[0] = 0;
                dx[1] = 0, dy[1] = -1;
                dx[2] = 1, dy[2] = 0;
                dx[3] = 0, dy[3] = 1;
                n = 4;
                break;
        case 'E' :
        case 'e' :
                dx[0] = -1, dy[0] = -1;
                dx[1] = -1, dy[1] = 1;
                dx[2] = 1, dy[2] = -1;
                dx[3] = 1, dy[3] = 1;
                n = 4;
                break;
        case 'C' :
                dx[0] = 0, dy[0] = -1;
                n = 1;
                break;
        case 'c' :
                dx[0] = 0, dy[0] = 1;
                n = 1;
                break;
        case 'H' :
                dx[0] = -1, dy[0] = 0;
                dx[1] = -1, dy[1] = -1;
                dx[2] = 0, dy[2] = -1;
                dx[3] = 1, dy[3] = -1;
                dx[4] = 1, dy[4] = 0;
                dx[5] = 0, dy[5] = 1;
                n = 6;
                break;
        case 'h' :
 		dx[0] = -1, dy[0] = 0;
                dx[1] = -1, dy[1] = 1;
                dx[2] = 0, dy[2] = -1;
                dx[3] = 1, dy[3] = 1;
                dx[4] = 1, dy[4] = 0;
                dx[5] = 0, dy[5] = 1;
                n = 6;
                break;
        case 'L' :
        case 'l' :
                dx[0] = -1, dy[0] = 0;
                dx[1] = -1, dy[1] = -1;
                dx[2] = 0, dy[2] = -1;
                dx[3] = 1, dy[3] = -1;
                dx[4] = 1, dy[4] = 0;
                dx[5] = 1, dy[5] = 1;
                dx[6] = 0, dy[6] = 1;
                dx[7] = -1, dy[7] = 1;
                n = 8;
                break;
        }

        return n;
}

int point_base(char piece) // catch point of each piece
{
        switch(piece)
        {
	case 'o' :
		return 0;        
	case 'g' :
	case 'G' :
                return 5;
        case 'e' :
	case 'E' :
                return 3;
        case 'h' :
	case 'H' :
                return 7;
        case 'c' :
	case 'C' :
                return 1;
        case 'l' :
	case 'L' :
                return 100;
        }
}

void my_hand_ctrl(char piece, char my_hand[], int type) //adjust my hand when catch enemy piece or place
{
        int i;

        if (piece == 'H')
                piece = 'C';
		
        if ((type) && (piece != 'o')) //move
        {
                my_hand[strlen(my_hand)] = piece;
                my_hand[strlen(my_hand) + 1] = '\0';
        }
        else if (type == 0) //place
        {
                for (i = 0; i < 10; i++)
                {
                        if (my_hand[i] == piece)
                        {
                                strcpy(my_hand + i, my_hand + i + 1);
                                break;
                        }
                }
        }
}

void change_upper_lower(char *piece) //change only when it is not 'o'
{
        if (islower(*piece) && (*piece != 'o'))
                *piece -= 32;
        else if (!islower(*piece))
                *piece += 32;
}

void change_position(State *state) //change position each other
{
        int i, j;
        char p1, p2;
        char tmp[10];

        for (i = 0; i < 2; i++)
        {
                for (j = 0; j < 3; j++)
                {
                        p1 = state->board[i][j];
                        p2 = state->board[3-i][2-j];

                        change_upper_lower(&p1);
                        change_upper_lower(&p2);

                        state->board[i][j] = p2;
                        state->board[3-i][2-j] = p1;
                }
        }

        for (i = 0; i < (int)strlen(state->my_hand); i++)
        {
                state->my_hand[i] += 32; //upper to lower
        }
        for (j = 0; j < (int)strlen(state->en_hand); j++)
        {
                state->en_hand[j] -= 32; //lower to upper
        }

        strcpy(tmp, state->my_hand);
	clear_str(state->my_hand);
        strcpy(state->my_hand, state->en_hand);
	clear_str(state->en_hand);
        strcpy(state->en_hand, tmp);

        state->point = -state->point;
}

void clear_str(char string[]) //clear string array which is 10 length 
{
	int i;
	
	for (i = 0; i < 10; i++)
	{
		string[i] = '\0';
	}
}

int point_of_field(State *state, int type) //0 : enemy, 1 : my, point of pieces on the board
{
        int point = 0;
        int i, j;
        char c;

        for (i = 0; i < 4; i++)
        {
                for (j = 0; j < 3; j++)
                {
                        c = state->board[i][j];

                        if (c == 'o')
                                continue;

                        if ((islower(c) && !type) || (!islower(c) && type))
                                point += point_base(c);
                }
        }
        return point;
}

int max(int a, int b) //return big number
{
	if (a < b)
		return b;
	else
		return a;
}
