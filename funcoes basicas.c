#include <stdio.h>

typedef struct elemento{
	int dado;
	struct elemento* proximo;
} t_elemento;

typedef struct lista{
	t_elemento* inicio;
	t_elemento* fim;
} t_lista;

typedef struct pilha{
	t_lista* l;
}t_pilha;

int insereinicio(int valor, t_lista* l){
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

int removeinicio(t_lista* l){
	if(estavazia(l)){
		printf("Lista vazia\n");
		return -1;
	}
	t_elemento* p = l -> inicio;
	int tmp = p -> dado;

	l -> inicio = p -> proximo;
	free(p);
	if(l -> inicio == NULL){
		l -> fim = NULL;
	}
	return tmp;
}

t_lista* crialista(){
	t_lista* l = (t_lista*)malloc(sizeof(t_lista));
	l->inicio=NULL;
	l->fim=NULL;
	return l;
}

int inserefim(int valor, t_lista* l){
	t_elemento* nv;

	nv = (t_elemento*)malloc(sizeof(t_elemento));
	nv -> dado = valor;
	nv -> proximo = NULL;
	if(l -> inicio == NULL){
		l -> inicio = nv; 
	}
	else{
		l -> fim -> proximo = nv;
	}
	l -> fim = nv;
	return 0;
}

int estavazia(t_lista* l){
	if(l -> inicio == NULL){
		return 1;
	}
	return 0;
}
/*Algs pilha*/

t_pilha* criapilha(){
	t_pilha* p = (t_pilha*)malloc(sizeof(t_pilha));
	p->l = crialista();
	return p;
}

void empilhar(int valor, t_pilha* p){
	insereinicio(valor, p->l);
}

int desempilhar(t_pilha* p){
	return removeinicio(p->l);
}

void desempilharTudo(t_pilha*p){
	int tmp;

	while(p->l->inicio != NULL){
		tmp = removeinicio(p->l);
		printf("Removido %d\n", tmp);
	}
}

void mostraPilha(t_pilha* p){
	if(p->l->inicio == NULL){
		printf("Pilha vazia\n");
	}
	else{
		mostralista(p->l);
	}
}