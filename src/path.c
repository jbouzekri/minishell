/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Source contenant les fonctions pour gerer la variable d'environnement PATH
**/

#include "header.h"


void getPath()
{
	int i, start = 0,j,k;
	int length = 0;
	
	char* ppath = getenv("PATH");
	
	int path_length = strlen(ppath);
	
	for (i=0;i<path_length;i++) {
	
		if (ppath[i] == ':') {
			Node* node = list_add_elem(&paths);
			node->data = malloc((length+1)*sizeof(char));
	
			if (node->data == NULL) { printf("Memory fault"); exit(1); }
	
			k = 0;
	
			for (j=start;j<i;j++) {
				node->data[k] = ppath[j];
				k++;
			}
	
			node->data[k] = '\0';
	
			length = 0;
			start = i + 1;
		} else length++;
	
	}
	
	Node* node = list_add_elem(&paths);
	node->data = malloc((length+1)*sizeof(char));
	
	if (node->data == NULL) { printf("Memory fault"); exit(1); }
	
	k = 0;
	
	for (j=start;j<path_length;j++) { //on traite le dernier path
		node->data[k] = ppath[j];
		k++;	
	}
	
	node->data[k] = '\0';
	flag_path = true;
	
	if (DEBUG) print_list(&paths);
}

void changePath(char *ppath)
{
	
	int start = 5,i,j,k;
	int length = 0;
	int path_length = strlen(ppath);
	Node* node;	
	if(flag_path == true && paths.begin != NULL) freeList(&paths);
	
	for (i=5;i<path_length;i++) {
		if (i == path_length-1 && ppath[i] == ':') {
			node = list_add_elem(&paths);
			node->data = malloc((length+1)*sizeof(char));
	
			if (node->data == NULL) { printf("Memory fault\n"); exit(1); }
	
			k = 0;
	
			for (j=start;j<i;j++) {
				node->data[k] = ppath[j];
				k++;
			}
			
			node->data[k] = '\0';
			length = 0;
			start = i + 1;
			node = list_add_elem(&paths);
			node->data = malloc((2)*sizeof(char));
			node->data[0] = '.';
			node->data[1] = '\0';
		} 
		else if (ppath[i] == ':') {
			node = list_add_elem(&paths);
			node->data = malloc((length+1)*sizeof(char));
	
			if (node->data == NULL) { printf("Memory fault\n"); exit(1); }
	
			k = 0;
	
			for (j=start;j<i;j++) {
				node->data[k] = ppath[j];
				k++;
			}
			
			node->data[k] = '\0';
			length = 0;
			start = i + 1;
		}
		else length++;
	}

	if (ppath[path_length-1] != ':') {
		node = list_add_elem(&paths);
		node->data = malloc((length+1)*sizeof(char));
	
		if (node->data == NULL) { printf("Memory fault\n"); exit(1); }
	
		k = 0;
		for (j=start;j<path_length;j++) { //on traite le dernier path
			node->data[k] = ppath[j];
			k++;	
		}
		node->data[k] = '\0';
	}
	flag_path_change = true;
	
	if (DEBUG) print_list(&paths);
}

void print_env(char **arg)
{
	int i=0,length=0;
	
	length = sizeof(arg);
	
	if (!strcmp(arg[1],"$PATH")) 
			print_list(&paths);
	
	else if (!strcmp(arg[1],"$HOME")) 
			printf("%s\n",getenv("HOME"));
	else {
		for (i=1;i<length-1;i++) printf("%s ",arg[i]);
		printf("\n");
	}
}

/* Non utilisee */
void addPath(char *new_path, List *list) 
{
	int length = strlen(new_path);
	printf("%d\n",length);
	Node* node = list_add_elem(&paths);
	node->data = malloc((length+1)*sizeof(char));
	
	if (node->data == NULL) { printf("Memory fault\n"); exit(1); }
	
	node->data = ".\0";
	
	if (DEBUG) print_list(&paths);
}
