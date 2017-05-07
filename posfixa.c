#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
	char dado;
	struct elemento* proximo;
} t_elemento;

typedef struct lista{
	t_elemento* inicio;
	t_elemento* fim;
} t_lista;

typedef struct pilha{
	t_lista* l;
}t_pilha;

typedef struct fila{
	t_lista* l;
}t_fila;

/*ALGORITMOS DE LISTA!*/

int insereinicio(char valor, t_lista* l){
	t_elemento* nv;

	nv = (t_elemento*)malloc(sizeof(t_elemento)); 
	nv -> dado = valor;
	nv -> proximo = l->inicio;
	l -> inicio = nv;
	if(l -> fim == NULL){
		l -> fim = nv;
	} 
	return 0;
}

int estavazia(t_lista* l){
	if(l -> inicio == NULL){
		return 1;
	}
	return 0;
}

char removeinicio(t_lista* l){
	if(estavazia(l)){
		printf("Lista vazia\n");
		return '\0';
	}
	t_elemento* p = l -> inicio;
	char tmp = p -> dado;

	l -> inicio = p -> proximo;
	free(p);
	if(l -> inicio == NULL){
		l -> fim = NULL;
	}
	return tmp;
}

/*FIM ALGORITMOS LISTA*/

/*ALGORITMO PILHAS*/

t_pilha* criapilha(){
	t_pilha* p = (t_pilha*)malloc(sizeof(t_pilha));
	p->l = crialista();
	return p;
}

void empilhar(char valor, t_pilha* p){
	insereinicio(valor, p->l);
}

int desempilhar(t_pilha* p){
	return removeinicio(p->l);
}

void mostraPilha(t_pilha* p){
	if(p->l->inicio == NULL){
		printf("Pilha vazia\n");
	}
	else{
		mostralista(p->l);
	}
}

/*FIM ALGORITMO PILHAS*/