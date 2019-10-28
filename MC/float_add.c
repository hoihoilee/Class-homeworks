#include <stdio.h>
#include <time.h>

void main() {
	long i;
	int s, e;
	float arr[16], add = 0.001;

	for (i = 0; i < 16; i++)
		arr[i] = 0.001;

	s = clock();
	for (i = 0; i < 100000000; i++) {
		arr[0] += add;
		arr[1] += add;
		arr[2] += add;
		arr[3] += add;
		arr[4] += add;
		arr[5] += add;
		arr[6] += add;
		arr[7] += add;
		arr[8] += add;
		arr[9] += add;
		arr[10] += add;
		arr[11] += add;
		arr[12] += add;
		arr[13] += add;
		arr[14] += add;
		arr[15] += add;
	}
	e = clock();

	for (i = 0; i < 16; i++)
		printf("%lf ", arr[i]);
	printf("\nrunning time : %lfms\n", (double)(e-s)/1000);
	printf("FLOPS : %lfGhz\n", 1600000/(double)(e-s));
	return;
}					
