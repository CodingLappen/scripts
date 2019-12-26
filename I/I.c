#include <stdio.h>

int main (int argc, char **args ) {
	int i = 1;
	printf("I "); 
	for ( ;i< argc ; i++ ) {
		printf("%s ", args[i]);
	}
	return 0;
	printf("\n");

	printf("\n");
	printf("\n");
	putchar(EOF);
}
