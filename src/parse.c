/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Source contenant les fonctions pour parser les commandes rentrees par l'utilisateur
**/



#include "header.h"

void parseCommand(char* command,int size_command)
{
	int i;
	boolean flag_exec= false;
	
	if (DEBUG) printf("\nSize Command : %d\n",size_command); 
	for (i=0;i<size_command;i++) {
		if(command[i] == '>'){ // recuperation des parametres de redirection de sortie
			i = parseCherchenom(command,i,&file_sortie,false);
		}
		else if(command[i] == '<'){ // recuperation des parametres de redirection d'entree
			i = parseCherchenom(command,i,&file_entree,true);
		}
		else if(command[i] == '&' && i == (size_command-2)){ // presence du & en fin de chaine
			flag_background = true;
		}
		else if(command[i] != ' ' 
			&& command[i] !='\0' 
			&& command[i] !='\n'
			&& command[i] !='\r'
			&& command[i] !=EOF
			&& flag_exec == false){
		
			i = parseExec(command,i);
			flag_exec = true;
		}
	}
	if (DEBUG) print_path_var( &file_sortie );
	if (DEBUG) print_path_var( &file_entree );
	
}

int parseCherchenom(char * command,int position,List *list,boolean flag_sens){
			
	int nbrchar =0, nbrspace =0, debut, i;
	Node* node;
	
	debut = position = position+1;
	
	while(command[position] == ' '){
		position++;
		nbrspace++;
	}
	
	while(command[position] != ' ' && 
		command[position] !='\0'&& 
		command[position] != '&'&& 
		command[position] != '>'&& 
		command[position] != '<'&&
		command[position] != '\r'&&
		command[position] != '\n' &&
		command[position] != EOF){
		position++;
		nbrchar++;
	}
	
	if (DEBUG) printf("Nbr char / Nrb space : %d %d\n",nbrchar,nbrspace);
	
	if(nbrchar !=0){ // si le nom ne comporte pas de caractères il n'est pas traité
		node = list_add_elem(list);
		node->data = malloc( (nbrchar+1)*sizeof(char) );
		if (node->data == NULL) { printf("Memory fault\n"); exit(1); }
		
		for(i=0;i<nbrchar;i++){
				(node->data)[i] =  command[debut+nbrspace+i];
		}
		
		(node->data)[nbrchar] = '\0';
		if(flag_sens == true) flag_file_entree = true;
		else flag_file_sortie = true;
	}
	
	return position-1;
}

int parseExec(char * command,int position){
	int debut, i, nbrchar = 0,nbrspace = 0;
	char * buffer;
	char * pch;
	char * executable ;
	
	debut = position ;
	if(command[debut] != '/' && command[debut] != '.' ) flag_relative = true;
		
	while(command[position] != ' ' && 
		command[position] !='\0'&& 
		command[position] != '&'&& 
		command[position] != '>'&& 
		command[position] != '<'&&
		command[position] != '\r'&&
		command[position] != '\n' &&
		command[position] != EOF){
		position++;
		nbrchar++;
	}
	
	if (DEBUG) printf("nbrchar : %d\n",nbrchar);
	
	exec = malloc ( (nbrchar+1)*sizeof(char) );
	if (exec == NULL) { printf("Memory fault\n"); exit(1); }	

	for(i=0;i<nbrchar;i++){
		exec[i] =  command[debut+i];
	}
	exec[nbrchar] =  '\0';
	
	if (DEBUG) printf("commande : %s\n",exec);	
	
	debut = position ;
	nbrchar = 0;
	
	while(command[position] == ' '){
		position++;
		nbrspace++;
	}
	
	while(command[position] !='\0'&& 
		command[position] != '&'&& 
		command[position] != '>'&& 
		command[position] != '<'&&
		command[position] != '\r'&&
		command[position] != '\n' &&
		command[position] != EOF){
		position++;
		nbrchar++;
	}
	
	
	if(nbrchar != 0){ // recuperation de l'executable et de ses parametres
		if(!flag_relative){ // gestion de l'adresse relative ou absolue
			executable = strrchr ( exec, '/');
			nbrarg = 1;
			arg = realloc (arg, nbrarg* sizeof(char*));
			if (arg == NULL) { printf("Memory fault\n"); exit(1); }
			arg[0] = malloc((strlen(executable)+1)*sizeof(char));
			if (arg[0] == NULL) { printf("Memory fault\n"); exit(1); }
			strcpy (arg[0] ,executable);
			if (DEBUG) printf ("%s\n",arg[0]);
		}else{
			nbrarg = 1;
			arg = realloc (arg, nbrarg* sizeof(char*));
			if (arg == NULL) { printf("Memory fault\n"); exit(1); }
			arg[0] = malloc((strlen(exec)+1)*sizeof(char));
			if (arg[0] == NULL) { printf("Memory fault\n"); exit(1); }
			strcpy (arg[0] ,exec);
			if (DEBUG) printf ("%s\n",arg[0]);
		}
		
		buffer = malloc ((nbrchar+1)*sizeof(char));
		if (buffer == NULL) { printf("Memory fault\n"); exit(1); }
		for(i=0;i<nbrchar;i++){
			buffer[i] =  command[debut+nbrspace+i];
		}
		buffer[nbrchar] =  '\0';
		
		
		pch = strtok (buffer," ");
		while (pch != NULL){
			nbrarg++;
			arg =  realloc (arg, nbrarg * sizeof(char*));
			if (arg == NULL) { printf("Memory fault\n"); exit(1); }
			arg[nbrarg-1] = malloc((strlen(pch)+1)*sizeof(char));
			if (arg[nbrarg-1] == NULL) { printf("Memory fault\n"); exit(1); }
			strcpy (arg[nbrarg-1] ,pch);
			if (DEBUG) printf ("%s\n",arg[nbrarg-1]);
			pch = strtok (NULL, " ");
		}
		
		arg =  realloc (arg, (nbrarg+1) * sizeof(char*));
		if (arg == NULL) { printf("Memory fault\n"); exit(1); }
		arg[nbrarg] = NULL;
		
		free(buffer);
	}
	return position -1;
}
