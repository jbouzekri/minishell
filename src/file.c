/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Fonctions de gestion des fichiers d'entree, de sortie et binaires
**/


#include "header.h"

char* find_bin( List* list, char* bin )
{
	int i;
	for (i = 0; i < PATH_MAX; i++) {
			pbin[i] = 0;
	}
	Node* node;
 	int length = 0;
	for(node=list->begin;node;node=node->next) {
		strcat(pbin,(char*)node->data);
		length = strlen(node->data);
		if (node->data[length-1] != '/') strcat(pbin,"/"); // test si le path fini par un "/"
		strcat(pbin, bin );
		if (DEBUG) printf("bin : %s\n",pbin);
		if (!file_exist(pbin)) {
			return (char*)pbin;
		}
		for (i = 0; i < PATH_MAX; i++) {
			pbin[i] = 0;
		}
	}
	return (char*)1;		
}


int file_exist(char* path)
{
	FILE* pfile = NULL;
	pfile = fopen ( path , "r" );
	if (pfile == NULL) return 1;
	else {
		fclose(pfile);
		return 0;
	} 
}

char* find_file( List *list )
{	
	FILE* pfile = NULL;
	Node* node;
 	for(node=list->begin;node;node=node->next) {
		pfile = fopen ( (char*)node->data, "a" );
		if ((Node*)node->next == NULL) {
			fclose(pfile);
			return (char*)node->data;
		}
		else {
			fclose(pfile);
		}
	}
	return (char*) 1;
}

