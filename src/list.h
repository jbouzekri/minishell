/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Definition des structures de listes chainees pour stocker les fichiers d'entree et de sortie (de redirection),
*	les variables d'environnement ainsi que la commande et ses parametres
**/

/* Noeud d'une liste chainee */
typedef struct _Node
{
        struct _Node *next;
        char *data;
} Node;

/* Extremite de la structure de liste chainee */
typedef struct _List
{
        Node *begin;
	Node *end;
} List;

Node* list_add_elem( List *list ); /* Ajouter un element a la fin de la liste chainee */
int print_list( List *list ); /* Imprime la liste chainee a l'ecran */
void freeList( List* list ); /* libere la memoire allouee a la liste chainee */

List paths; /* liste des variables d'environnement PATH */
List file_entree; /* liste des fichiers d'entree de redirection recuperes au parsage de la commande */
List file_sortie; /* liste des fichiers de sortie de redirection recuperes au parsage de la commande */
List command_parse; /* liste chainee contenant la commande a executer et ses parametres apres parsage */

