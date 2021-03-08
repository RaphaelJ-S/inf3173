#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <limits.h>
#include <dirent.h>

typedef struct 
{
	int n;
	int R;
	int iFich;	
}opt_t;
void verifierOptions(int, char**, opt_t*);
int afficherDir(char*, opt_t*);
int afficher(char*, opt_t*);
void verifierOptions(int _argc, char** _argv, opt_t* _options) 
{
	for(int i = 0; i < _argc; ++i) 
	{
		if(strcmp(_argv[i], "-n") == 0) 
		{
			_options->n =1;
			_options->iFich += 1;	
		}
		else if (strcmp(_argv[i], "-R") == 0) 
		{
			_options->R = 1;
			_options->iFich += 1;
		}
	}
}
int afficherDir(char* _entree, opt_t* _opt) 
{
	struct dirent* dataDir = NULL;	
	DIR* dirDesc = opendir(_entree);
	char path[PATH_MAX * 2 + 5] = "";
	if(!dirDesc) 
	{
		perror("Erreur dans l'ouverture du répertoire");	
		return 1;
	}
	readdir(dirDesc);
	readdir(dirDesc);	
	while((dataDir = readdir(dirDesc))) 
	{
		strcpy(path, _entree);	
		strcat(path, "/");	
		strcat(path, dataDir->d_name);	
		afficher(path, _opt);
	}
	return 0;
}
int afficher(char* _entree, opt_t* _opt) 
{
	struct stat statbuf, sb;
	char fichier_source[PATH_MAX * 2 +5] = ""; // 2 fois la longueur maximale + de l'espace pour la flèche
	char type[100];
	struct passwd * pw = NULL;
	struct group * gr = NULL;
	char permission[4] = "";
	char droits[20] = "";
	char Date_modification[30] = "";

	if (lstat(_entree, &statbuf) == -1) {
					perror("Erreur de la récupération des informations");
					return 1;
	}
	switch (statbuf.st_mode & S_IFMT) {
		case S_IFDIR:
						strcpy(type, "répertoire");
						break;
		case S_IFLNK:
						strcpy(type, "lien symbolique");
						break;
		case S_IFREG:
						strcpy(type, "fichier standard");
						break;
		default:
					strcpy(type, "Autre");
					break;
	}

	sprintf(permission, "%o", statbuf.st_mode & 0777);

	for (int j = 0; j < 4; j++) {
					switch (permission[j]) {
					case '0':
									strcat(droits, "---");
									break;
					case '1':
									strcat(droits, "--x");
									break;
					case '2':
									strcat(droits, "-w-");
									break;
					case '3':
									strcat(droits, "-wx");
									break;
					case '4':
									strcat(droits, "r--");
									break;
					case '5':
									strcat(droits, "r-x");
									break;
					case '6':
									strcat(droits, "rw-");
									break;
					case '7':
									strcat(droits, "rwx");
									break;

					}
	}
	
	pw = getpwuid(statbuf.st_uid);
	gr = getgrgid(statbuf.st_gid);

	strftime(Date_modification, 30, "%b %e %H:%M", localtime( & statbuf.st_mtime));

	
	printf("| %-12ld | %-11s | %-11s   | %-19ld ", 
				 statbuf.st_ino, droits, type, statbuf.st_nlink); 
	if(_opt->n == 1) 
		printf("| %-11s | %-6s ", pw->pw_name, gr->gr_name);
	else if(_opt->n == 0) 
		printf("| %-11u | %-6d ", pw->pw_uid, gr->gr_gid);
	
	printf("| %-11ld | %-21s |", statbuf.st_size, Date_modification);
	if (strcmp(type, "répertoire") == 0) {
					printf("\033[1;34m");
					printf(" %s \n", _entree);
					printf("\033[0m");
	} else if (strcmp(type, "fichier standard") == 0 && (statbuf.st_mode & 0111)) {
					printf("\033[1;32m");
					printf(" %s \n", _entree);
					printf("\033[0m");
	} else if (strcmp(type, "lien symbolique") == 0) {
					readlink(_entree, fichier_source, statbuf.st_size + 1);
					if (stat(_entree, & sb) == -1) {
									printf("\033[1;31m");
									printf(" %s ", _entree);
									printf("\033[0m");
									printf("->");
									printf("\033[1;31m");
									printf(" %s\n", fichier_source);
									printf("\033[0m");
					} else {
									printf("\033[1;36m");
									printf(" %s ", _entree);
									printf("\033[0m");
									printf("-> %s\n", fichier_source);
					}
	} else {
					printf(" %s \n", _entree);
	}
	if(strcmp(type, "répertoire") == 0) 
	{
		if(afficherDir(_entree, _opt) == 1)
			return 1;		
	}
	return 0;
}
int main(int argc, char * argv[]) {
	opt_t opt = {0,0,1};				
	if (argc < 2) {
		printf("Usage: %s [-n] [-R] fichier1 [fichier2 ...]\n", argv[0]);
		return 1;
	}
	printf("| Numéro inode | Droits      | Type               | Nombre de lien durs | Utilisateur | Groupe  | Taille      | Dernière modification | fichier                    \n");
	verifierOptions(argc, argv, &opt);
	for (int i = opt.iFich; i < argc; i++) {
		if(afficher(argv[i], &opt) == 1)
			return 1;	
	}
	return 0;
}
