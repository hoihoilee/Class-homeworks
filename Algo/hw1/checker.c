#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
	if (argc != 4) return;

        int i = atoi(argv[1]), j;
	int N = atoi(argv[3]);
        FILE *file = fopen(argv[2], "r");
        if (file == NULL) return;

        char line[1024];
        int *A = (int*)malloc(sizeof(int)), size = 0;

        while (fgets(line, sizeof(line), file) != NULL) {
                char *token = strtok(line, " \n\t");
                while (token != NULL) {
                        A = (int*)realloc(A, sizeof(int)*(size+1));
                        A[size] = atoi(token);
                        size++;
                        token = strtok(NULL, " \n\t");
                }
        }
	fclose(file);
	if ((i < 1) || (i > size)) return;

	int curr = 1, cnt = 0;
	
	for (j = 0; j < size; j++) {
		if (A[j] > N) continue;
		if (A[j] == N) cnt++; //cnt : count the number of given number N
		else curr++; //curr : number N's current ranking
		if ((curr > i) || ((i - curr - cnt + 1) > (size - j - 1))) break;
	}
	if ((i >= curr) && (i <= curr + cnt - 1)) printf("True\n");
	else printf("False\n");
	free(A);
	return;
}
