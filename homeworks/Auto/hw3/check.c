#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define size 100000

void main() {
	char *str = (char*)malloc(sizeof(char)*size);
	scanf("%s", str);
	printf("%d\n", (int)strlen(str));
}
