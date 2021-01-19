#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	char *phrase = malloc(400);
	char** tab;	
	if(argc < 2) {
		perror("Pas d'arguement contenant un fichier");
		return 2;	
	}
	
	FILE* file = fopen(argv[1],"r");
	if(!file) {
		perror(argv[1]);
		return 1;
	}
	while (fgets(phrase, 400, file)) {
		printf("\nPhrase : %s", phrase);
		//il faut mettre les phrases dans un tableau et le trier avec strcmp	
	}
	return 0;	
}
