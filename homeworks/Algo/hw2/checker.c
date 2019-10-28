#include <stdio.h>
#include <stdlib.h>

int to_int(char string[]) { //extract the output value
	int i;
	for (i = 0; i < 20; i++) {
		if (string[i] == ':') return atoi(string+i+2);
	}
}

void main(int argc, char *argv[]) {
        if (argc != 3) return;

        FILE *file = fopen(argv[1], "r");
        if (file == NULL) return;

        FILE *outfile = fopen(argv[2], "r");
	if (outfile == NULL) return;

        char line[10], outline[20];
        int A[999], i;
	for (i = 0; i < 999; i++) {
		A[i] = 0;
	}

        while (fgets(line, sizeof(line), file) != NULL) {
		if (fgets(outline, sizeof(outline), outfile) == NULL) {
			printf("Not Correct\n");
			return;
		}

                char inst = line[0];
                int N = atoi(line + 2);
		int out_N = to_int(outline);
                if (inst == 'I') {
                        if (A[N-1] == 0) A[N-1]++;
			else N = 0; //already exist

			if (out_N != N) {
				printf("Not Correct\n");
				return;
			}
	        }
                else if (inst == 'D') {
                        if (A[N-1] != 0) A[N-1]--;
                        else N = 0; //not exist

                        if (out_N != N) {
                                printf("Not Correct\n");
                                return;
                        }
                }
                else if (inst == 'S') {
                        int tmp = 0;
			for (i = 0; i < 999; i++) {
				if (A[i] == 0) continue;

				N--;
				if (N < 1) {
					tmp = i+1;
					break;
				}
			}
			if (out_N != tmp) {
				printf("Not Correct\n");
                                return;
			}
                }
                else {
                        int tmp = 0;
			if (A[N-1] != 0) {
				for (i = 0; i < N; i++) {
					if (A[i] == 0) continue;
					tmp++;
				}
			}
			if (out_N != tmp) {
                                printf("Not Correct\n");
                                return;
                        }
                }
        }
	if (fgets(outline, sizeof(outline), outfile) != NULL) {
        	printf("Not Correct\n");
                return;
        }
	printf("Correct\n");
        fclose(file);
        fclose(outfile);
        return;
}
