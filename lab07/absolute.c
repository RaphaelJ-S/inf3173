#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int _argc, char** _argv) 
{
	struct dirent* dirData= NULL;	
	DIR* dirDescrip = NULL;
	char path[PATH_MAX * 2] = "";
	ino_t inode = 0;
	ino_t inodeParent = 1;	
	ino_t tmp = 0;
	char nom[PATH_MAX] = ".";
	char dotPath[PATH_MAX] = ".";
	while(inode != inodeParent) 
	{
		if(!(dirDescrip = opendir(dotPath))) 
		{
			perror("erreur dans l'ouverture du répertoire");
			return -1;
		}
		dirData = readdir(dirDescrip); 
		inode = dirData->d_ino;
		dirData = readdir(dirDescrip);
		inodeParent = dirData->d_ino;
		strcat(dotPath, "/..");	
		while((dirData = readdir(dirDescrip))) 
		{
			if(dirData->d_ino == tmp) 
			{
				strcpy(nom, dirData->d_name);
				strcat(nom, "/");	
				strcat(nom, path);
				strcpy(path, nom);
			}
			
		}
		tmp = inode;
		closedir(dirDescrip);
	}
	printf("\n/%s\n", path);
	return 0;
}
