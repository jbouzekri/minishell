/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Header de minishell contenant l'ensemble des prototypes
**/


#define SIZE_BUFFER 255
#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include "list.h"

typedef enum {true = 1, false = 0} boolean; /* Definition du type boolean */

void traitement(int numero_signal); /* capture du ctrl+C */
void freeMemory();	/* Liberation de la memoire apres execution */

void getPath(void); /* recupere la variable d'environnement PATH au demarrage */
void changePath(char *ppath); /* modifie la variable d'environnement PATH */
void print_env(char **arg); /* affiche la variable d'environnement demandee (uniquement HOME et PATH) */ 
void addPath(char *new_path, List *list); /* rajoute un path a la variable d'environnement PATH */

void parseCommand(char* command,int size_command); /* methode pour parser la commande saisie par l'utilisateur */
int parseCherchenom(char * command,int position,List *list,boolean flag_sens); /* gestion des cas particuliers lors du parsage (redirection) */
int parseExec(char * command,int position); /* recuperation de la commande a executer et de ses parametres */

void execCommand(); /* execution de la commande */
void execCD(char command[]); /* execution de la commande interne cd */

char* find_file( List *list ); /* gestion des fichiers de redirection de la sortie */
char* find_bin( List* list, char* bin ); /* fonction qui recherche l'executable parmi les PATH */
int file_exist(char* path); /* test l'existence d'un fichier */

boolean flag_background; /* execution du processus fils en "background" */
boolean flag_file_sortie; /* presence de fichier pour la redirection de sortie */
boolean flag_file_entree; /* presence de fichier pour la redirection d'entree */
boolean flag_relative; /* commande taper en relatif */
boolean flag_path; /* recuperation de la variable d'environnement PATH a l'initialisation */
boolean flag_path_change; /* changement de PATH par l'utilisateur */

char* path; /* repertoire courant */
char **arg ; /* tableau des arguments de la commande */
char *exec ; /* commande appelee */
int nbrarg; /* nombre d'arguments recupere */

char pbin[ PATH_MAX ]; /* variable indiquant l'emplacement du binaire */
char * username; /* variable contenant le nom de l'utilisateur */

