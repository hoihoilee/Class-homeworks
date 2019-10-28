#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int N; //the number of NFA states
int *N_final, ***N_tran; //N_final : NFA final states, N_tran : NFA transition
int M, M_string[100][101]; //M : # of strings, M_string[n]'s first bit : length
int **C; //temporal state

void E_closure(int n, int sw) {//start from 'n' state, closure set -> C[sw]
	int i;
	C[sw][n] = 1;
	for (i = 0; i < N; i++) {
		if (N_tran[2][n][i] == 0) continue;
		if (C[sw][i] == 0) E_closure(i, sw);
	}
	return;
}

void run_NFA(int m) { //running NFA for M_string[m]
	int i, j, k, s = 0, w = 1;
	memset(C[0], 0, sizeof(int)*N);
	E_closure(0, 0);

	for (i = 1; i <= M_string[m][0]; i++) {
		memset(C[w], 0, sizeof(int)*N);
		for (j = 0; j < N; j++) {
			if (C[s][j] == 0) continue;
			for (k = 0; k < N; k++) {
				if (N_tran[M_string[m][i]][j][k] == 0) continue;

				E_closure(k, w);
			}
		}
		if (s == 0) {
			s = 1;
			w = 0;
		}
		else {
			s = 0;
			w = 1;
		}
	}
	for (i = 0; i < N; i++) {
		if (C[s][i] == 0) continue;
		if (N_final[i] == 1) {
			printf("Yes\n"); //accept
			return;
		}
	}
	printf("No\n"); //not accept
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

	scanf("%d", &M);
	for (i = 0; i < M; i++) {
		char tmp[110];
		scanf("%s", tmp);
		M_string[i][0] = strlen(tmp);
		for (j = 0; j < strlen(tmp); j++) {
			if (tmp[j] == '0') M_string[i][j+1] = 0;
			else M_string[i][j+1] = 1;
		}
	}

	//Running NFA

	C = (int**)malloc(sizeof(int*)*2);
	C[0] = (int*)malloc(sizeof(int)*N);
	C[1] = (int*)malloc(sizeof(int)*N);

	for (i = 0; i < M; i++)
		run_NFA(i);

	//free memory

	free(C[0]);
	free(C[1]);
	free(C);

	for (i = 0; i < 3; i++) {
		for (j = 0; j < N; j++)
			free(N_tran[i][j]);
		free(N_tran[i]);
	}
	free(N_tran);
	free(N_final);

	return;
}
