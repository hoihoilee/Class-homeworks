#include <stdio.h>

void main() {
	int N = 100000, i, j;
	FILE *file = fopen("input.txt", "w");
	while (N > 0) {
		for (j = 0; j < 20; j++) {
			fprintf(file, "%d ", N);
			N--;
			if (N < 1) break;
		}
		fprintf(file, "\n");
	}
	fclose(file);
}
