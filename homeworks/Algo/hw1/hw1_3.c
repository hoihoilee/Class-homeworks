#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *A, int *B) { //swap A and B
	int tmp = *A;
	*A = *B;
	*B = tmp;
	return;
}

int partition(int A[], int pivot, int p, int r) {//partition by element of which index is matched with given pivot
	int i;
	int q = p;
	swap(&A[pivot], &A[r]);
	for (i = p; i < r; i++) {
		if (A[i] < A[r]) {
			swap(&A[q], &A[i]);
			q++;
		}
	}
	swap(&A[q], &A[r]);
	return q;
}

int d_partition(int A[], int pivot, int size) { //partition by element which is matched with given pivot
	int i;
	int q = 0, index;
	for (i = 0; i < size; i++) {
		if (A[i] > pivot) continue;
		swap(&A[q], &A[i]);
		if (A[q] == pivot) index = q;
		q++;
	}
	swap(&A[q - 1], &A[index]);
	return (q - 1);
}

int random_select(int A[], int p, int r, int i) {
	if (p == r) return A[p];
	int q = partition(A, rand()%(r-p+1)+p, p, r); //randomly choose pivot
	int k = q - p + 1;
	if (i < k) return random_select(A, p, q - 1, i);
	else if (i == k) return A[q];
	else return random_select(A, q + 1, r, i - k);
}

int five_sort(int A[], int size, int i) { //insertion sort in size 5
        int j, k, tmp;
        for (j = 1; j < size; j++) {
                tmp = A[j];
                for (k = j - 1; k >= 0; k--) {
                        if (A[k] > tmp) A[k + 1] = A[k];
                        else break;
                }
                A[k + 1] = tmp;
        }
        return A[i - 1];
}

int deter_select(int A[], int size, int i) {
	if (size <= 5) return five_sort(A, size, i); //if size is less than 5, just sort them
	int j;
	int group_n = size / 5, last = size % 5; // last : the number of last group's element
	if (last > 0) group_n++;
	
	int *group = (int*)malloc(sizeof(int)*group_n);  // group : list of medians, group_n : the number of medians
	for (j = 0; j < (group_n - 1); j++) group[j] = five_sort(A + (j * 5), 5, 3);
	if (last == 0) group[j] = five_sort(A + (j * 5), 5, 3);
	else group[j] = five_sort(A + (j * 5), last, (last + 1) / 2);

	int pivot = deter_select(group, group_n, (group_n + 1) / 2); //pivot : median of group's elements (get value recursively)
	free(group);

	int q = d_partition(A, pivot, size);
	int k = q + 1;
	if (i < k) return deter_select(A, q, i);  //left side of pivot
	else if (i == k) return A[q];
	else return deter_select(A + q + 1, size - q - 1, i - k); //right side of pivot
}

void main(int argc, char *argv[]) {
	if (argc != 3) return;

	int i = atoi(argv[1]);
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
	int *B = (int*)malloc(sizeof(int)*size), j, start, end;
	for (j = 0; j < size; j++) B[j] = A[j];

	if ((i < 1) || (i > size)) return;

	printf("[Randomized select result]\n");
	start = clock();
	printf("%d element : %d\n", i, random_select(A, 0, size - 1, i));
	end = clock();
	printf("Running time : %.2lfms\n", (double)(end - start)/1000);
	printf("[Deterministic select result]\n");
	start = clock();
	printf("%d element : %d\n", i, deter_select(B, size, i));
	end = clock();
	printf("Running time : %.2lfms\n", (double)(end - start)/1000);

	fclose(file);
	free(A);
	free(B);
	return;
}
