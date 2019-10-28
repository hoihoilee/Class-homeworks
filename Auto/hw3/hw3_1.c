#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 100000 //tape size

typedef struct _tran { //element of transition table
	int next; //next state number
	char change; //character to be changed
	int move; //S: 0, L: -1, R: 1
} tran;

int char_num(char A) { //return the table number for the given character
	if (A == '0') return 0;
	if (A == '1') return 1;
	if (A == '#') return 2;
	return (int)A - 94;
}

int run(tran **table, char *halt, char *tape) { //run the turing machine
	int i, head = 0, state = 0; //initialize the state and head of the tape with 0
	
	while (halt[state] != '1') { //running until the halt state
		i = char_num(tape[head]);
		if (table[state][i].next == -1) return -1; //infinite loop

		tape[head] = table[state][i].change; //change the character of the current head
		head += table[state][i].move; //move the head
		state = table[state][i].next; //go to next state
	}

	return 0;
}

void print_tape(char *tape) { //print the tape
	int i, j, sw = 0, len = 0;

	for (i = 0; i < size; i++) {
		if (tape[i] == '#') {
			len++;
			continue;
		}
		if (sw == 0) {
			sw = 1;
			len = 0;
		}
		else {
			for (j = 0; j < len; j++)
				printf("%c", '#');
			len = 0;
		}
		printf("%c", tape[i]);
	}
	printf("\n");

	return;
}

void main() {
	//input stage

	int i, j;
	int N, K;
 	char *halt, *tape; //halt: halt states
  tran **table; //transition table

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

	tape = (char*)malloc(sizeof(char)*size);
	for (i = 0; i < size; i++)
		tape[i] = '#'; //initialize the tape with blank character '#'

	scanf("%s", tape+1);
	tape[strlen(tape)] = '#';

	//run the TM and print the tape
	
	if (run(table, halt, tape) == 0) print_tape(tape);
	else printf("Error\n");

	//free memory

	for (i = 0; i < N; i++)
		free(table[i]);
	free(table);
	free(halt);
	free(tape);

	return;
}
