/**
*	Renard Simon
*	Lian Liu
*	Bouzekri Jonathan 
*	
*	le 27/09/2007 - Realisation d'un minishell
*
*	Fonctions de manipulation des listes chainees definies dans le header list.h
**/



#include "header.h"

Node* list_add_elem( List *list )
{
	Node *node =  malloc( sizeof( Node ) );
	if (node == NULL) { printf("Memory fault\n"); exit(1); }
	if( node == NULL ) return NULL;
	node->data = NULL;
	node->next = NULL;
	
	if( list->end ) list->end->next = node;
	else {
		list->begin = node;
		list->end = node;
	}
	list->end=node;
	if (DEBUG) printf("Add element\n");
	return node;
}

void freeList( List* list )
{
	Node* node = list->begin;
	Node* pnode= list->begin;
	
	node = pnode->next;
	while (pnode->next != NULL) {
		free(pnode->data);
		free(pnode);
		pnode = node;
		node = node->next;
		if (DEBUG) printf("remove element\n");
	}
	free(pnode->data);
	free(pnode);
	if (DEBUG) printf("remove element end\n");
	list->begin = NULL;
	list->end = NULL;
}

int print_list( List *list )
{
	Node* node;
	for(node=list->begin;node;node=node->next)
		printf("%s%s",(char*)node->data,node->next ? ":" : "");
		printf("\n");
	return 0;
}

