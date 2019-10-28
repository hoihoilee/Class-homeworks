#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _rule {
	char name; //variable name
	int size; //number of productions
	char prod[3]; //productions
} rule;

void find_R1(rule *Rs, int R_n, char *A, char a) { //find all variable names to 'A', which generates 'a' ('a' is terminal)
	int i, j = 0;
	for (i = 0; i < R_n; i++) {
		if (Rs[i].size != 1) continue; //not terminal rule
		if (Rs[i].prod[0] != a) continue; //do not generate 'a'

		A[j] = Rs[i].name; //save this rule's name
		j++;
	}
	A[j] = '\0';

	return;
}

void find_R2(rule *Rs, int R_n, char *A, char *BC) { //find all variable names to 'A', which generates 'BC' ('BC' consists of two variables) 
	int i, j = 0;
	for (i = 0; i < R_n; i++) {
		if (Rs[i].size != 2) continue; //terminal rule
		if (strcmp(Rs[i].prod, BC) != 0) continue; //do not generate 'BC'

		A[j] = Rs[i].name; //save this rule's name
		j++;
	}
	A[j] = '\0';

	return;
}

void merge_str(char *x, char *y) { //merge 'x' with 'y' ('x & y' are rule name list)
	int i, j = strlen(x);
	for (i = 0; i < strlen(y); i++) {
		if (strchr(x, y[i]) != '\0') continue; // 'x' already has 'y''s i-th element

		x[j] = y[i]; //add 'y''s element to 'x'
		j++;
		x[j] = '\0';
	}

	return;
}

int CYK(rule *Rs, int R_n, char ***matrix, char *w, int w_len) { //CYK algorithm, if grammer accepts the string 'w', return 1 else, return 0
	int i, j, k, a, b, d;
	char *tmp = (char*)malloc(sizeof(char)*(R_n+1)); //for saving the variable names

	for (i = 0; i < w_len; i++) { //for each letter 'a' of string 'w'
		strcpy(matrix[i][i], ""); //initialize V_ii
		find_R1(Rs, R_n, tmp, w[i]); //find rules which generates 'a'
		merge_str(matrix[i][i], tmp); //save to V_ii
	}

	for (d = 1; d < w_len; d++) {
		for (i = 0; i < (w_len-d); i++) {
			j = i+d;
			strcpy(matrix[i][j], ""); //initialize V_ij
			for (k = i; k < j; k++) {
				for (a = 0; a < strlen(matrix[i][k]); a++) {
					for (b = 0; b < strlen(matrix[k+1][j]); b++) {
						char tmp2[3]; //for 'BC'
						tmp2[0] = matrix[i][k][a]; //for variable 'B' in V_ik
						tmp2[1] = matrix[k+1][j][b]; //for variable 'C' in V_(k+1)j
						tmp2[2] = '\0';
						find_R2(Rs, R_n, tmp, tmp2); //find rules which generates 'BC'
						merge_str(matrix[i][j], tmp); // V_ij is merged with set of rules which generate 'BC'
					}
				}
			}
		}
	}
	free(tmp);
	
	if (strchr(matrix[0][w_len-1], Rs[0].name) == '\0') return 0; //if start variable is not in the V_0(w_len-1), this grammer doesn't accept string 'w'
	else return 1; //else, accept
}
					
void main() {
	//input stage
	int i, j;
	int R_n;
	scanf("%d", &R_n);
	rule *Rs = (rule*)malloc(sizeof(rule)*R_n);

	for (i = 0; i < R_n; i++) {
		char tmp[10];
		scanf("%s", tmp);
		Rs[i].size = strlen(tmp)-2;
		Rs[i].name = tmp[0];
		for (j = 0; j < strlen(tmp)-2; j++)
			Rs[i].prod[j] = tmp[j+2];
		Rs[i].prod[j] = '\0';
	}
	char w[55]; //input string
	scanf("%s", w);
	int w_len = strlen(w); //string's length

	char ***matrix = (char***)malloc(sizeof(char**)*w_len); //matrix for V_ij
	for (i = 0; i < w_len; i++) {
		matrix[i] = (char**)malloc(sizeof(char*)*w_len);
		for (j = 0; j < w_len; j++) {
			matrix[i][j] = (char*)malloc(sizeof(char)*(R_n+1));
		}
	}

	//CYK algorithm
	if (CYK(Rs, R_n, matrix, w, w_len) == 1) printf("Yes\n");
	else printf("No\n");
	
	//free memory
	free(Rs);
	for (i = 0; i < w_len; i++) {
		for (j = 0; j < w_len; j++)
			free(matrix[i][j]);
		free(matrix[i]);
	}
	free(matrix);

	return;
}
