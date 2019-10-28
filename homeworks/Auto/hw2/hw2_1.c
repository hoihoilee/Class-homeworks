#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _rule {
	char name[10]; //variable name
	int size; //number of productions
	char prod[50][10]; //productions
} rule;

int is_var(char *x) {// x: production
	if (strlen(x) > 1) return 1;
	if (((x[0] >= 'a') && (x[0] <= 'z')) ||
			((x[0] >= 'A') && (x[0] <= 'Z')))
		return 1; // x is variable

	return 0; //x is terminal
}

int rule_type(rule R) {//0: not unit, 1: terminal, 2: unit production
	if (R.size > 1) return 0;
	if (is_var(R.prod[0]) == 0) return 1;
	
	return 2;
}

void print_R(rule *Rs, int R_n, char *start) { //print the Rules
	int i, j, start_i = -1;
	printf("%d\n", R_n);
	for (i = 0; i < R_n; i++) {
		if (strcmp(Rs[i].name, start) == 0) { //print start variable first
			start_i = i;
			printf("<%s>:", Rs[i].name);
			for (j = 0; j < Rs[i].size; j++) {
				if (is_var(Rs[i].prod[j]) == 1)
					printf("<%s>", Rs[i].prod[j]);
				else
					printf("%s", Rs[i].prod[j]);
			}
			printf("\n");
			break;
		}
	}
	for (i = 0; i < R_n; i++) { //print other variables
		if (start_i == i) continue;
			
		printf("<%s>:", Rs[i].name);
		for (j = 0; j < Rs[i].size; j++) {
			if (is_var(Rs[i].prod[j]) == 1)
				printf("<%s>", Rs[i].prod[j]);
			else
				printf("%s", Rs[i].prod[j]);
		}
		printf("\n");
	}
	return;
}

int same_R(rule R1, rule R2) { //if R1 and R2 are same return 1 else 0
	int i;
	if (strcmp(R1.name, R2.name) != 0) return 0;
	if (R1.size != R2.size) return 0;
	for (i = 0; i < R1.size; i++)
		if (strcmp(R1.prod[i], R2.prod[i]) != 0) return 0;
	return 1;
}

int insert_R(rule *Rs, int R_n, rule input_R) { //insert the input_R to the Rs (not duplicate)
	int i;
	for (i = 0; i < R_n; i++)
		if (same_R(Rs[i], input_R) == 1) return R_n; //there already exists input_R in the Rs

	Rs[R_n] = input_R;
	R_n++;
	return R_n;
}

int copy_R(rule *R1, rule *R2, int r2) { //copy the R2 to the R1
	int i;
	for (i = 0; i < r2; i++)
		R1[i] = R2[i];

	return r2;
}

int DFS_R(rule *Rs, int R_n, rule *new_R, int new_n, char *Name, int index, int *visit) { //DFS for unit production (continuously apply production rule until not unit production)
	int i;
	visit[index] = 1; //visited
	for (i = 0; i < R_n; i++) {
		if (strcmp(Rs[index].prod[0], Rs[i].name) != 0) continue;
		if (visit[i] == 1) continue;
		//next production rule

		if (rule_type(Rs[i]) != 2) { //not unit production (DFS end)
			visit[i] = 1;
			rule input_R = Rs[i];
			strcpy(input_R.name, Name);
			new_n = insert_R(new_R, new_n, input_R); //insert new rule (ex: A => BC, insert A -> BC)
		}
		else new_n = DFS_R(Rs, R_n, new_R, new_n, Name, i, visit); //continuously apply production rule
	}
	return new_n;
}	

int stage1(rule *Rs, int R_n) { //remove unit productions
	int i, j, new_n = 0;
	rule *new_R = (rule*)malloc(sizeof(rule)*100000);

	for (i = 0; i < R_n; i++) {
		if (rule_type(Rs[i]) != 2) //not unit production
			new_n = insert_R(new_R, new_n, Rs[i]);
		else {
			int *visit = (int*)malloc(sizeof(int)*R_n); //for DFS
			for (j = 0; j < R_n; j++)
				visit[j] = 0;

			new_n = DFS_R(Rs, R_n, new_R, new_n, Rs[i].name, i, visit); //this unit production rule changed to not unit production rules
			free(visit);
		}
	}
	R_n = copy_R(Rs, new_R, new_n); //copy the new rules to 'Rs'
	free(new_R);

	return R_n;
}

int term_num(char *x) { //return the terminal's number
	if (strcmp(x, "0") == 0) return 0;
	if (strcmp(x, "1") == 0) return 1;
	if (strcmp(x, "2") == 0) return 2;
	if (strcmp(x, "3") == 0) return 3;
	if (strcmp(x, "4") == 0) return 4;
	if (strcmp(x, "5") == 0) return 5;
	if (strcmp(x, "6") == 0) return 6;
	if (strcmp(x, "7") == 0) return 7;
	if (strcmp(x, "8") == 0) return 8;
	if (strcmp(x, "9") == 0) return 9;
	if (strcmp(x, "+") == 0) return 10;
	if (strcmp(x, "-") == 0) return 11;
	if (strcmp(x, "*") == 0) return 12;
	if (strcmp(x, "/") == 0) return 13;
	if (strcmp(x, "(") == 0) return 14;
	return 15;
}

void X_n(char *x, int n) { //given n, make name of variable x (ex: "X3" when n = 3)
	int i = n, len = 1;
	x[0] = 'X';
	if (n == 0) {
		x[1] = '0';
		x[2] = '\0';
		return;
	}
	
	while(i > 0) {
		len *= 10;
		i /= 10;
	}
	i = 1;
	while(len > 1) { //itoa
		len /= 10;
		x[i] = (char)(n/len + 48);
		n = n % len;
		i++;
	}
	x[i] = '\0';

	return;
}

int stage2(rule *Rs, int R_n) { //last step of chomsky normalizing
	int i, j;
	rule *new_R = (rule*)malloc(sizeof(rule)*100000); //for new rules whose type of "A->BC"
	int new_n = 0;

	int term_used[16];
	rule *term = (rule*)malloc(sizeof(rule)*16); //rules of making terminals
	for (i = 0; i < 16; i++) {
		term_used[i] = 0;
		char T[10];
		T[0] = 'T';
		if (i < 10) T[1] = (char)(i+48); //terminal rule's name (ex: "T3" for terminal '3')
		else T[1] = (char)(i+87);
		T[2] = '\0';
		strcpy(term[i].name, T);
		term[i].size = 1;
		if (i < 10) strcpy(term[i].prod[0], T+1);
		else if (i == 10) strcpy(term[i].prod[0], "+");
		else if (i == 11) strcpy(term[i].prod[0], "-");
		else if (i == 12) strcpy(term[i].prod[0], "*");
		else if (i == 13) strcpy(term[i].prod[0], "/");
		else if (i == 14) strcpy(term[i].prod[0], "(");
		else strcpy(term[i].prod[0], ")");
	}

	for (i = 0; i < R_n; i++) {
		if (rule_type(Rs[i]) == 1) continue; //it's already chomsky normal form

		for (j = 0; j < Rs[i].size; j++) {
			if (is_var(Rs[i].prod[j]) != 0)	continue;
			int num = term_num(Rs[i].prod[j]);
			strcpy(Rs[i].prod[j], term[num].name); // change the terminal to the variable
			if (term_used[num] == 0) term_used[num] = 1; // and add the new terminal rule
		}

		while(Rs[i].size > 2) { // make type of "A->BC"
			int sw = 0;
			for (j = 0; j < new_n; j++) { //if 'new_R' has the rule, just change
				if ((strcmp(new_R[j].prod[0], Rs[i].prod[Rs[i].size-2]) == 0) &&
						(strcmp(new_R[j].prod[1], Rs[i].prod[Rs[i].size-1]) == 0)) {
					strcpy(Rs[i].prod[Rs[i].size-2], new_R[j].name);
					Rs[i].size--;
					sw = 1;
					break;
				}
			}
			if (sw == 1) continue;

			rule input_R; //else, add the new rule
			char x[10];
			X_n(x, new_n); //new rule's name
			strcpy(input_R.name, x);
			input_R.size = 2;
			strcpy(input_R.prod[0], Rs[i].prod[Rs[i].size-2]);
			strcpy(input_R.prod[1], Rs[i].prod[Rs[i].size-1]);
			strcpy(Rs[i].prod[Rs[i].size-2], input_R.name);
			Rs[i].size--;
			new_R[new_n] = input_R;
			new_n++;
		}
	}

	for (i = 0; i < 16; i++) { //merge new rules with Rs
		if (term_used[i] == 1) {
			Rs[R_n] = term[i];
			R_n++;
		}
	}
	for (i = 0; i < new_n; i++) { //merge new rules with Rs
		Rs[R_n] = new_R[i];
		R_n++;
	}
	free(new_R);
	free(term);

	return R_n;
}

void main() {
	//input stage
	int i, j;
	int R_n;
	scanf("%d", &R_n);
	rule *Rs = (rule*)malloc(sizeof(rule)*100000);
	char start[10]; //start variable name

	for (i = 0; i < R_n; i++) {
		char tmp[55];
		scanf("%s", tmp);
		Rs[i].size = strlen(tmp)-2;
		strncpy(Rs[i].name, tmp, 1);
		Rs[i].name[1] = '\0';
		for (j = 0; j < strlen(tmp)-2; j++) {
			strncpy(Rs[i].prod[j], tmp+j+2, 1);
			Rs[i].prod[j][1] = '\0';
		}
	}
	strcpy(start, Rs[0].name);

	//chomsky normal form
	R_n = stage1(Rs, R_n);
	R_n = stage2(Rs, R_n);
	print_R(Rs, R_n, start);

	//free memory
	free(Rs);

	return;
}
