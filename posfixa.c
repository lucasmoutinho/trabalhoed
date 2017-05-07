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

t_lista* criaLista(){
	t_lista* l = (t_lista*)malloc(sizeof(t_lista));
	l->inicio=NULL;
	l->fim=NULL;
	return l;
}

void insereInicio(char valor, t_lista* l){
	t_elemento* nv;
	nv = (t_elemento*)malloc(sizeof(t_elemento)); 
	nv->dado = valor;
	nv->proximo = l->inicio;
	l->inicio = nv;
	if(l->fim == NULL){
		l->fim = nv;
	}
}

void insereFim(char valor, t_lista* l){
	t_elemento* nv;
	nv = (t_elemento*)malloc(sizeof(t_elemento));
	nv->dado = valor;
	nv->proximo = NULL;
	if(l->inicio == NULL){
		l->inicio = nv; 
	}
	else{
		l->fim->proximo = nv;
	}
	l->fim = nv;
}

int estaVazia(t_lista* l){
	if(l->inicio == NULL){
		return 1;
	}
	return 0;
}

char removeInicio(t_lista* l){
	if(estaVazia(l)){
		return '\0';
	}
	t_elemento* p = l->inicio;
	l->inicio = p->proximo;
	char tmp = p->dado;
	free(p);
	if(l->inicio == NULL){
		l->fim = NULL;
	}
	return tmp;
}

void removeTudo(t_lista* l){
	while(l->inicio != NULL){
		removeInicio(l);
	}
}

/*FIM ALGORITMOS LISTA*/

/*ALGORITMO PILHAS*/

t_pilha* criaPilha(){
	t_pilha* p = (t_pilha*)malloc(sizeof(t_pilha));
	p->l = criaLista();
	return p;
}

void empilhar(char valor, t_pilha* p){
	insereInicio(valor, p->l);
}

int desempilhar(t_pilha* p){
	return removeInicio(p->l);
}

int pilhaVazia(t_pilha* p){
	if(p->l->inicio == NULL){
		return 1;
	}
	return 0;
}

/*FIM ALGORITMO PILHAS*/

/*INFIXA TO POSFIXA*/

int priorMaiorOuIgual(char atual,char c){
	if(c == '*'||c == '/'){
		if(atual == '+'||atual == '-'||atual == '('){
			return 1;
		}
		return 0;
	}
	else if(c == '+'||c == '-'){
		if(atual == '('){
			return 1;
		}
		return 0;
	}
	return 0;
}

t_lista* convertePosfixa(t_lista* infixa){
	t_lista* posfixa = criaLista();
	t_pilha* pilha = criaPilha();
	t_elemento* atual = infixa->inicio;
	char desempilhado = '\0';
	while(atual!=NULL){
		if(atual->dado == '*'||atual->dado == '/'||atual->dado == '+'||atual->dado == '-'||atual->dado == '('||atual->dado == ')'){
			if(atual->dado == ')'){
				desempilhado = desempilhar(pilha);
				while(desempilhado != '('){
					insereFim(desempilhado, posfixa);
					desempilhado = desempilhar(pilha);
				}
				desempilhado = '\0';
			}
			else{
				while(!pilhaVazia(pilha) && priorMaiorOuIgual(atual->dado,pilha->l->inicio->dado)){
					insereFim(desempilhar(pilha), posfixa);
				}
				empilhar(atual->dado, pilha);
			}
		}
		else{
			insereFim(atual->dado,posfixa);
			printf("%c\n", atual->dado);
		}
		atual = atual->proximo;
	}
	while(!pilhaVazia(pilha)){
		insereFim(desempilhar(pilha), posfixa);
	}
	removeTudo(infixa);
	free(infixa);
	return posfixa;
}

int main(){
	t_lista* infixa;
	t_lista* posfixa;
	t_elemento* atual;
	infixa = criaLista();
	insereFim('A', infixa);
	insereFim('*', infixa);
	insereFim('(', infixa);
	insereFim('B', infixa);
	insereFim('+', infixa);
	insereFim('C', infixa);
	insereFim(')', infixa);
	insereFim('/', infixa);
	insereFim('D', infixa);
	atual = infixa->inicio;
	while(atual!=NULL){
		printf("%c ", atual->dado);
		atual = atual->proximo;
	}
	printf("\n");
	posfixa = convertePosfixa(infixa);
	atual = posfixa->inicio;
	while(atual!=NULL){
		printf("%c ", atual->dado);
		atual = atual->proximo;
	}
	printf("\n");
	return 0;
}

