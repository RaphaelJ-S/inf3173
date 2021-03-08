#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

int main(int _argc, char** _argv) {
	pid_t pid_fils;
	int wstatut;
	int exit_statut = 0;

	pid_fils = fork();
	if(pid_fils == -1) {
		perror("Echec du fork");
		exit(EXIT_FAILURE);
	}	else if (pid_fils == 0) {
		execvp(_argv[1], _argv + 1);	//"/bin/ls", "ls", "/etc", NULL
		perror("La commande ne peut être exécuté");
		exit(EXIT_FAILURE);
	}
	pid_fils = waitpid(-1, &wstatut, 0);
	if(pid_fils == -1) {
		perror("Erreur de waitpid");
		exit(EXIT_FAILURE);
	}

	if(WIFEXITED(wstatut)) {
		exit_statut = WEXITSTATUS(wstatut);
		printf("\nL'exécution de la commande est terminée, avec le code de retour %d. \n", exit_statut);
	}
	exit(exit_statut);
}
