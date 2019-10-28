#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <time.h>

typedef struct node *p_node;
typedef struct node {
	int number;
	p_node next;
} node;

typedef struct stack {
        p_node top;
} stack;

typedef struct array {
	int *count;
	int *number;
} array;

int *scc;
int scc_i;

int **A;   //Adjacency Matrix
p_node *B; //Adjacency List
array C;   //Adjacency Array

int **info;
int N;
int idx;
stack *S;

int min(int a, int b) {
	if (a < b) return a;
	return b;
}

void scc_sort(int start, int end) { //insertion sort
        int i, j, tmp;
        for (i = start+1; i <= end; i++) {
                tmp = scc[i];
                for (j = i - 1; j >= start; j--) {
                        if (scc[j] < tmp) scc[j + 1] = scc[j];
                        else break;
                }
                scc[j + 1] = tmp;
        }
        return;
}

void S_push(int n) {
        p_node tmp = (p_node)malloc(sizeof(node));
        tmp->number = n;
        tmp->next = S->top;
        S->top = tmp;
        return;
}

int S_pop() {
        if (S->top == NULL) return -1;

        int ret = S->top->number;
        p_node tmp = S->top->next;
        free(S->top);
        S->top = tmp;
        return ret;
}

void S_clear() {
	while(S->top != NULL) {
		S_pop();
	}
	return;
}

void reset() { //setting for SCC
	int i;
	memset(scc, -1, sizeof(int)*2*(N+1));
	scc_i = 1;
	idx = 0;
	S_clear();
	for (i = 0; i < N; i++) {
                info[i][0] = -1; //index
                info[i][1] = -1; //lowlink
                info[i][2] = 0;  //on Stack
        }
	return;
}

void print_scc(FILE *outfile) {
	int i, j, check = 0;
	int *tmp = (int*)malloc(sizeof(int)*N);
	memset(tmp, 0, sizeof(int)*N);

	for (i = 1; i < scc_i; i++) {
		if (scc[i] != -1) continue;

		scc_sort(check+1, i-1); //partial sort
		tmp[scc[i-1]] = i-1;
		check = i;
	}
	for (i = 0; i < N; i++) {
		if (tmp[i] == 0) continue;

		j = tmp[i];
		while(scc[j] != -1) {
			fprintf(outfile, "%d ", scc[j]+1);
			j--;
		}
		fprintf(outfile, "\n");
	}
	free(tmp);
	return;
}

void SCC_A(int v) { //Matrix SCC
	info[v][0] = idx;
	info[v][1] = idx;
	idx++;
	S_push(v);
	info[v][2] = 1;

	int w;
	for (w = 0; w < N; w++) {
		if (A[v][w] == 0) continue;

		if (info[w][0] == -1) { //DFS
			SCC_A(w);
			info[v][1] = min(info[v][1], info[w][1]);
		}
		else {
			if (info[w][2] == 1) info[v][1] = min(info[v][1], info[w][0]);
		}
	}
		
	if (info[v][0] == info[v][1]) { //when v is root
		do {
			w = S_pop();
			info[w][2] = 0;
			scc[scc_i++] = w; //save SCC element
		} while (w != v);
		scc[scc_i++] = -1; //end save
	}
	return;
}

void SCC_B(int v) { //List SCC
        info[v][0] = idx;
        info[v][1] = idx;
        idx++;
        S_push(v);
        info[v][2] = 1;

	int w;
        p_node tmp = B[v];
        while(tmp != NULL) {
		w = tmp->number;
                if (info[w][0] == -1) {
                        SCC_B(w);
                        info[v][1] = min(info[v][1], info[w][1]);
                }
                else {
                        if (info[w][2] == 1) info[v][1] = min(info[v][1], info[w][0]);
                }
		tmp = tmp->next;
        }

        if (info[v][0] == info[v][1]) {
                do {
                        w = S_pop();
                        info[w][2] = 0;
                        scc[scc_i++] = w;
                } while (w != v);
                scc[scc_i++] = -1;
        }
        return;
}

void SCC_C(int v) { //Array SCC
        info[v][0] = idx;
        info[v][1] = idx;
        idx++;
        S_push(v);
        info[v][2] = 1;

        int w;
        int i, start, end;
	if (v == 0) {
		start = 0;
		end = C.count[v];
	}
	else {
		start = C.count[v-1];
		end = C.count[v];
	}

        for (i = start; i < end; i++) {
                w = C.number[i];
                if (info[w][0] == -1) {
                        SCC_C(w);
                        info[v][1] = min(info[v][1], info[w][1]);
                }
                else {
                        if (info[w][2] == 1) info[v][1] = min(info[v][1], info[w][0]);
                }
        }

        if (info[v][0] == info[v][1]) {
                do {
                        w = S_pop();
                        info[w][2] = 0;
                        scc[scc_i++] = w;
                } while (w != v);
                scc[scc_i++] = -1;
        }
        return;
}

void main() {
	//=============================================<Read Input and Make adjacency matrix, list and array>========================
	FILE *file = stdin;
	FILE *out = stdout;

	int i, j;

	fscanf(file, "%d", &N);

	A = (int**)malloc(sizeof(int*)*N);
	for (i = 0; i < N; i++) {
        	A[i] = (int*)malloc(sizeof(int)*N);
                memset(A[i], 0, sizeof(int)*N);
	}
        B = (p_node*)malloc(sizeof(p_node)*N);
        C.count = (int*)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++) {
		int n, start;
		fscanf(file, "%d", &n);
		p_node link = NULL;
		if (i == 0) {
			C.count[i] = n;
                        C.number = (int*)malloc(sizeof(int)*n);
                        start = 0;
                }
                else {
                        C.count[i] = n + C.count[i-1];
                        C.number = (int*)realloc(C.number, sizeof(int)*C.count[i]);
                        start = C.count[i-1];
                }

		for (j = 0; j < n; j++) {
			int vertex;
			fscanf(file, "%d", &vertex);

			A[i][vertex-1] = 1;

			if (link == NULL) {
                                B[i] = (p_node)malloc(sizeof(node));
                                B[i]->number = vertex-1;
                                B[i]->next = NULL;
                                link = B[i];
                        }
                        else {
                                p_node tmp_node = (p_node)malloc(sizeof(node));
                                tmp_node->number = vertex-1;
                                tmp_node->next = NULL;
                                link->next = tmp_node;
                                link = link->next;
                        }

                        C.number[start++] = vertex-1;
		}
	}
	//=====================================================<Strongly Connected Components>============================
	scc = (int*)malloc(sizeof(int)*2*(N+1));
	info = (int**)malloc(sizeof(int*)*N);
	for (i = 0; i < N; i++) { 
		info[i] = (int*)malloc(sizeof(int)*3);
	}
	S = (stack*)malloc(sizeof(stack));
	S->top = NULL;

	int t_start, t_end;

	reset();

	t_start = clock();
	for (i = 0; i < N; i++) {
		if (info[i][0] == -1) SCC_A(i);
	}
	t_end = clock();
	printf("<Adjacency Matrix>\n");
	print_scc(out);
	printf("running time : %.2lfms\n", (double)(t_end - t_start)/1000);

	reset();

	t_start = clock();
        for (i = 0; i < N; i++) {
                if (info[i][0] == -1) SCC_B(i);
        }
	t_end = clock();
	printf("<Adjacency List>\n");
	print_scc(out);
	printf("running time : %.2lfms\n", (double)(t_end - t_start)/1000);

        reset();

	t_start = clock();
        for (i = 0; i < N; i++) {
                if (info[i][0] == -1) SCC_C(i);
        }
	t_end = clock();
	printf("<Adjacency Array>\n");
	print_scc(out);
	printf("running time : %.2lfms\n", (double)(t_end - t_start)/1000);

	//===================================================<Free Memory>================================================

	for (i = 0; i < N; i++) {
		free(A[i]);
		free(info[i]);
		p_node tmp1 = B[i];
		p_node tmp2 = NULL;
		while(tmp1 != NULL) {
			tmp2 = tmp1->next;
			free(tmp1);
			tmp1 = tmp2;
		}
	}	
	free(A);
	free(B);
	free(C.count);
	free(C.number);
	free(info);
	free(scc);
	free(S);

        return;
}
