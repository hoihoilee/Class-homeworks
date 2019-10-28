#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "move.h"
#include "common.h"

int main()
{
	State tmp, *state = &tmp; //declare state as State type pointer
	State next_state[256];

	read_game(state);
	
	int best = strategy(state, next_state);
	
	if (best == -1)
		printf("give_up\n");
	else
		print_mov(state, &next_state[best]);
}
