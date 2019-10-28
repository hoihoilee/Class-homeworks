#include <stdio.h>
#include <time.h>

void main() {
	long i;
	int s, e;
	float arr[16], mul = 1.000000001;

	for (i = 0; i < 16; i++)
		arr[i] = 0.001;

	s = clock();
	for (i = 0; i < 100000000; i++) {
		arr[0] *= mul;
		arr[1] *= mul;
		arr[2] *= mul;
		arr[3] *= mul;
		arr[4] *= mul;
		arr[5] *= mul;
		arr[6] *= mul;
		arr[7] *= mul;
		arr[8] *= mul;
		arr[9] *= mul;
		arr[10] *= mul;
		arr[11] *= mul;
		arr[12] *= mul;
		arr[13] *= mul;
		arr[14] *= mul;
		arr[15] *= mul;
	}
	e = clock();

	for (i = 0; i < 16; i++)
		printf("%lf ", arr[i]);
	printf("\nrunning time : %lfms\n", (double)(e-s)/1000);
	printf("FLOPS : %lfGhz\n", 1600000/(double)(e-s));
	return;
}					
