/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Source contenant le main (appel des fonctions de parsage, d'execution ..)
**/


#include "header.h"

/* le main va boucler à l'infini tant que le caracter EOF n'est pas recu
** il va lancer les fonctions de parse et d'executions*/
int main(int argc, char *argv[])
{
	int i,carac_number = 0;
	char command[SIZE_BUFFER +1]; // Buffer pour recuperer la commande
	
	signal(SIGINT, traitement); // capture du signal ctrl+C 

	/* Buffer pour stocker la commande avant parsage */
	
	flag_path = false;
		
	for(i=0;i<carac_number;i++) command[i] = 0;

	while (1) {
		/* flag d'etat de l'application */
		flag_file_sortie = false;
		flag_file_entree = false;
		flag_background = false;
		flag_relative = false;
		flag_path_change = false;		

		arg = NULL;
		nbrarg = 0;
		exec = NULL;
		
		if(flag_path == false) getPath();
			
		path = malloc (SIZE_BUFFER * sizeof(char));
		if (path == NULL) { printf("Memory fault\n"); exit(1); }		

		username = getlogin(); // recuperation du nom de l'utilisateur
		getcwd(path, SIZE_BUFFER); // recuperation du repertoire courant
	
		if (username != NULL) printf("%s : minishell %s $",username,path); // affichage du prompt
		else printf("minishell %s $",path);
		
		if (fgets ( command, SIZE_BUFFER, stdin ) == NULL) { // gestion du ctrl+D
				putchar('\n'); 
				freeMemory(0);
				exit(0); 
		} 
		else{ 
			carac_number = strlen(command);
			if (carac_number !=1) {
				if (DEBUG) printf("nbr carac %d",carac_number);
				parseCommand(command, carac_number); // chaine non vide, on parse la commande
				
				if(!strcmp(exec,"cd")){ // gestion du cd
					if(arg == NULL) execCD(getenv("HOME"));
					else execCD(arg[1]);
				}
				else if (!strncmp(exec,"PATH=",5)){ // gestion de la variable d'environnement PATH
					if (DEBUG) printf("changement de path\n");
					if (arg == NULL) {
						if (DEBUG) printf("pas d'espace on peut changer\n");
						changePath(exec);
					}
					else printf("erreur de syntaxe");
				}
				else if (!strncmp(exec,"echo",4)) { // affichage des variables d'environnement
						if (arg == NULL) printf("erreur de syntaxe\n");
						else print_env(arg);
				}
				else execCommand();
			}
		}	
		
		for(i=0;i<carac_number;i++) command[i] = 0;
		
		carac_number = 0;
		freeMemory(1); // Liberation de la memoire
	}

	return EXIT_SUCCESS;
}


void freeMemory(int j)
{
	int i;
	if (file_sortie.begin != NULL) freeList(&file_sortie);
	if (file_entree.begin != NULL) freeList(&file_entree);
	if((j==0 || flag_path == false ) && paths.begin != NULL ) freeList(&paths);
	if(exec != NULL) free(exec);
	if (path != NULL) free(path);
	if(arg != NULL){
		for(i=0;i<=nbrarg;i++) free(arg[i]);
		free(arg);
	}	
}


 void traitement(int numero_signal)
{
	switch (numero_signal) {
		case SIGINT:
		break;
          }
}
