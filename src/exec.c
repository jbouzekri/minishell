/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Source contenant les fonctions pour executer les commandes parses
**/




#include "header.h"

/* fonction qui va executer la commande dans un processus fils*/
void execCommand()
{
	int i;
	int status;
	char * executable = NULL;
	int pid = fork () ; // creation d'un processus fils qui executera la commande
	if ( pid < 0 ) { // il y a eu une erreur dans la creation du fils
		freeMemory();
		perror ( "echec du fork\n");
		exit(-1);
	}

	if ( pid > 0 ) { /* nous somme dans le processus pere */ 
		if(!flag_background) {
			while (wait(&status) != pid); // on attend la fin du fils si le flag & est positionne
		}
		
	}else{ /* nous sommes dans le processus fils */		
		if(flag_relative == true){
			executable = find_bin( &paths, exec );
		}else executable = exec;
		
		if(executable != (char*)(1)){
			
			if (DEBUG) printf("flag_file_entree = %d",flag_file_entree);
			
			if(flag_file_entree == true) freopen( find_file( &file_entree ) , "r", stdin);	// redirection d'entree
			if(flag_file_sortie == true)	freopen( find_file( &file_sortie ) , "a", stdout ); // redirection de sortie
			
			if(execv ( executable, arg) == -1) {
				printf("Erreur d'execution de la commande\n");
				exit(1);
			}
		}else{
			if (flag_path_change == false) printf("Commande inconnue\n");
			flag_path_change = false;
			exit(1);
		}
	}

}

void execCD(char * newpath)
{
	chdir(newpath);
}







