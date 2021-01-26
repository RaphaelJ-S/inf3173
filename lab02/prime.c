#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	
	cible = strtol(_argv[1], NULL,10); 
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
	long int *tabPrime = (long int*)malloc(sizeof(long int) * cap);
	bool prime;

	if(tabPrime == NULL) { 
		perror("allocation");
		return -1;
	}
	size_t nbrPrime = 0;

	for (long int i = 2 ; i <= _cible ; ++i) {
		prime = true;
		for( size_t k = 0 ; k < nbrPrime ; ++k ) {
			long int j = tabPrime[k];
			if (j > sqrt(i)) break;

			if (i%j == 0) {
				prime = false;
				break;
			}	
		}
		if( prime ) {
			tabPrime[nbrPrime] = i;
			nbrPrime++;
			if ( nbrPrime == cap ) {
				cap *= 2;
				tabPrime = (long int*)realloc(tabPrime, cap * sizeof(long int));
				if ( tabPrime == NULL ) { 
					perror("Allocation");
					return -1;
				}
			}
		}	
	}
	free(tabPrime);
	return nbrPrime;	
}
