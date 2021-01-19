


#include <stdlib.h>
#include <stdio.h>

int main() {
	FILE *pFile = fopen("lecture.txt","w+");	

	for ( int i = 1 ; i < 4 ; i++ ) {
		char *phrase = malloc(400);
		printf ("\nPhrase %d : ", i);
		scanf ("%399s", phrase);
		fputs(phrase, pFile);
		char *ligne = malloc(400);
		printf ("\nLigne %d : ", i+1);
		scanf ("%399s", ligne);
		fputs(ligne, pFile);
		free(phrase);
		free(ligne);
	}
	fclose(pFile);

}
