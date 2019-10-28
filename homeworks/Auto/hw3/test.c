#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _tran {
	int next; //next state number
	char change; //character to be changed
	int move; //S: 0, L: -1, R: 1
} tran;

void main() {
	//input stage

	int i, j;
	int N, K;
 	char *halt;
  tran **table;

	scanf("%d", &K);
	K += 3;
	scanf("%d", &N);
	halt = (char*)malloc(sizeof(char)*(N+1));
	scanf("%s", halt);

	table = (tran**)malloc(sizeof(tran*)*N);
	for (i = 0; i < N; i++) {
		table[i] = (tran*)malloc(sizeof(tran)*K);

		for (j = 0; j < K; j++) {
			char tmp[10];
			scanf("%s", tmp);
			if (tmp[0] == '-') table[i][j].next = -1;
			else table[i][j].next = atoi(tmp);

			scanf("%s", tmp);	
			table[i][j].change = tmp[0];

			scanf("%s", tmp);
			if (tmp[0] == 'S') table[i][j].move = 0;
			else if (tmp[0] == 'L') table[i][j].move = -1;
			else if (tmp[0] == 'R') table[i][j].move = 1;
			else table[i][j].move = 2;
		}
	}

	//run the TM and print the tape
	
	for (i = 0; i < N; i++) {
		printf("%d: ", i);
		for (j = 0; j < K; j++) {
			if (table[i][j].next == -1) printf("(-, -, -) ");
			else {
				printf("(%d, %c, ", table[i][j].next, table[i][j].change);
				if (table[i][j].move == 1) printf("R) ");
				else if (table[i][j].move == 0) printf("S) ");
				else printf("L) ");
			}
		}
		printf("\n");
	}

	//free memory

	for (i = 0; i < N; i++)
		free(table[i]);
	free(table);
	free(halt);

	return;
}
