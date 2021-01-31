#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char** argv) {
	printf("\netext : %p", etext);
	printf("\nedata : %p", edata);
	printf("\nend   : %p", end);
	printf("\nbrk   : %p", sbrk);
	pause();
	return 42;
}
