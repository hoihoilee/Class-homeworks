#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int N; //the number of NFA states
int *N_final, ***N_tran; //N_final : NFA final states, N_tran : NFA transition
int D, D_final[10000], D_tran[2][10000]; //D : # of DFA states, D_final : DFA final states, D_tran : DFA transition
int **state; //Q_D

int marked_state() {//return marked state
	int i;
	for (i = 0; i < D; i++)
		if (state[i][N] == 1) return i;

	return -1; // there's no marked state
}

void E_closure(int n, int state_num) {//start from 'n' state, closure set -> state[state_num]
	int i;
	state[state_num][n] = 1;
	for (i = 0; i < N; i++) {
		if (N_tran[2][n][i] == 0) continue;
		if (state[state_num][i] == 0) E_closure(i, state_num);
	}
	return;
}

int new_state(int stat_arr[]) { //if input state is new state return -1 else duplicate state num
	int i, j, check; //0: diff, 1: same
	for (i = 0; i < D; i++) {
		check = 1;
		for (j = 0; j < N; j++) {
			if (state[i][j] == stat_arr[j]) continue;
			check = 0;
			break;
		}
		if (check == 1) return i;
	}
	return -1;
}

void final_state() { //make DFA final state
	int i, j;
	for (i = 0; i < D; i++) {
		D_final[i] = 0;
		for (j = 0; j < N; j++) {
			if (state[i][j] == 0) continue;
			if (N_final[j] == 1) {
				D_final[i] = 1;
				break;
			}
		}
	}
	return;
}

void print_DFA() { //print DFA table
	int i;
	printf("%d\n", D);
	for (i = 0; i < D; i++)
		printf("%d %d %d %d\n", i, D_final[i], D_tran[0][i], D_tran[1][i]);
	
	return;
}

void main() {
	//input stage

	int i, j, k;
	scanf("%d", &N);
	N_final = (int*)malloc(sizeof(int)*N);
	N_tran = (int***)malloc(sizeof(int**)*3); //0: 0, 1: 1, 2: epsilon

	for (i = 0; i < 3; i++) {
		N_tran[i] = (int**)malloc(sizeof(int*)*N);
		for (j = 0; j < N; j++) {
			N_tran[i][j] = (int*)malloc(sizeof(int)*N);
			memset(N_tran[i][j], 0, sizeof(int)*N);
		}
	}

	for (i = 0; i < N; i++) {
		int n; //state number
		scanf("%d", &n);
		scanf("%d", &N_final[n]);
		for (j = 0; j < 3; j++) {
			char tmp[50];
			scanf("%s", tmp);
			if (tmp[0] == '-') continue;

			char *p = strtok(tmp, ",");
			while (p != NULL) {
				N_tran[j][n][atoi(p)] = 1;
				p = strtok(NULL, ",");
			}
		}
	}

	//NFA to DFA
	
	D = 0;
	state = (int**)malloc(sizeof(int*)*10001);
	for (i = 0; i < 10001; i++)
		state[i] = (int*)malloc(sizeof(int)*(N+1));

	memset(state[0], 0, sizeof(int)*(N+1));
	E_closure(0, 0); //Q_D <- E(q_0)
	state[0][N] = 1; //mark
	D++;

	int P = marked_state();

	while (P != -1) { //there exist marked state
		state[P][N] = 0; //unmark
		for (i = 0; i < 2; i++) {
			memset(state[D], 0, sizeof(int)*(N+1));
			for (j = 0; j < N; j++) {
				if (state[P][j] == 0) continue;

				for (k = 0; k < N; k++) {
					if (N_tran[i][j][k] == 0) continue;

					E_closure(k, D);
				}
			}
			int R = new_state(state[D]);
			if (R == -1) {//check it is new state
				state[D][N] = 1; //mark
				R = D;
				D++; //add state
			}
			D_tran[i][P] = R; //transition
		}
		P = marked_state();
	}

	final_state();

	print_DFA();

	//free memory

	for (i = 0; i < 10001; i++)
		free(state[i]);
	free(state);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < N; j++)
			free(N_tran[i][j]);
		free(N_tran[i]);
	}
	free(N_tran);
	free(N_final);

	return;
}
