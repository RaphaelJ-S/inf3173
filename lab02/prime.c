#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*
ldd prime : pour trouver toutes les lib dynamiquement liées lors de la compilation de prime


*/
size_t prime(const long int);

int main(int _argc, char** _argv) {
	long int cible;
	size_t nbrPrime;
	
	if (!(_argc == 2)) {
		printf("\nIl faut un seul argument\n");
		return -1;	
	}
	
	cible = strtol(_argv[1], NULL, sizeof(long int));	
	if(cible == 0) {
		puts("\nArgument invalide\n");
		return -1;
	}
	nbrPrime = prime(cible);
	
	printf("\nNombre de prime en dessous de %ld : %ld", cible, nbrPrime);
	printf("\n");
	return 0;
}

size_t prime(const long int _cible){
	size_t cap = 10;
	long int *tabPrime = malloc(sizeof(long int) * cap);
	size_t nbrPrime = 0;


	free(tabPrime);
	return nbrPrime;	
}
