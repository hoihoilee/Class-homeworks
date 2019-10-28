#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
        int N = atoi(argv[1]), i, j, prob = atoi(argv[2]), n = 0;
	int *number = (int*)malloc(sizeof(int)*(N-1));
        FILE *file = fopen("input.txt", "w");
	fprintf(file, "%d\n", N);
        for (i = 1; i <= N; i++) {
                for (j = 1; j <= N; j++) {
			if (i == j) continue;

                        if ((rand()%100) < prob) {
				number[n++] = j;
			}
                }
		fprintf(file, "%d", n);
		for (j = 0; j < n; j++) {
			fprintf(file, " %d", number[j]);
		}
		fprintf(file, "\n");
                n = 0;
        }
	free(number);
        fclose(file);
}
