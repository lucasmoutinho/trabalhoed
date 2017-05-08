#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Structs com char*/

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

/*Structs com inteiro*/

typedef struct elementoint{
	int dado;
	struct elementoint* proximo;
} t_elementoint;

typedef struct listaint{
	t_elementoint* inicio;
	t_elementoint* fim;
} t_listaint;

typedef struct pilhaint{
	t_listaint* l;
}t_pilhaint;

typedef struct filaint{
	t_listaint* l;
}t_filaint;

/*ALGORITMOS COM CHAR!*/

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

void esvaziaPilha(t_pilha*p){
	while(p->l->inicio != NULL){
		removeInicio(p->l);
	}
}

/*FIM ALGORITMOS COM CHAR*/

/*ALGORITMOS COM PILHA INT*/

t_listaint* criaListaint(){
	t_listaint* l = (t_listaint*)malloc(sizeof(t_listaint));
	l->inicio=NULL;
	l->fim=NULL;
	return l;
}

void insereInicioint(int valor, t_listaint* l){
	t_elementoint* nv;
	nv = (t_elementoint*)malloc(sizeof(t_elementoint)); 
	nv->dado = valor;
	nv->proximo = l->inicio;
	l->inicio = nv;
	if(l->fim == NULL){
		l->fim = nv;
	}
}

int estaVaziaint(t_listaint* l){
	if(l->inicio == NULL){
		return 1;
	}
	return 0;
}

int removeInicioint(t_listaint* l){
	if(estaVaziaint(l)){
		return '\0';
	}
	t_elementoint* p = l->inicio;
	l->inicio = p->proximo;
	int tmp = p->dado;
	free(p);
	if(l->inicio == NULL){
		l->fim = NULL;
	}
	return tmp;
}

t_pilhaint* criaPilhaint(){
	t_pilhaint* p = (t_pilhaint*)malloc(sizeof(t_pilhaint));
	p->l = criaListaint();
	return p;
}

void empilharint(int valor, t_pilhaint* p){
	insereInicioint(valor, p->l);
}

int desempilharint(t_pilhaint* p){
	return removeInicioint(p->l);
}

void esvaziaPilhaint(t_pilhaint*p){
	while(p->l->inicio != NULL){
		removeInicioint(p->l);
	}
}

/*ALGORITMOS COM PILHA INT*/

/*ALGORITMOS STRING DINAMICA*/

char* criaString(int n){
	char* string = (char*)malloc(n*sizeof(char));
	return string;
}

void ajustaString(char** string){
	*string = (char*)realloc(*string,(((int)strlen(*string)+1)*sizeof(char)));
}

char* leString(){
	char* infixa;
	infixa = criaString(151);
	scanf(" %s", infixa);
	getchar();
  	ajustaString(&infixa);
	return infixa;
}

/*FIM ALGORITMOS DE STRING DINAMICA*/

/*VALIDACAO INFIXA*/

int valida(char* infixa){
	int i = 0, continua, desempilhado;
	t_pilha* pilha = criaPilha();
	continua = 1;
	while (infixa[i]!='\0' && continua==1){
		if (infixa[i]=='('){
			empilhar(infixa[i], pilha);
		}
		else if (infixa[i]==')'){
			if (pilhaVazia(pilha)){
				continua = 0;
			}
			else {
				desempilhado = desempilhar(pilha);
				if(desempilhado==infixa[i]){
					continua = 0;
				}
			}
		}	
		i++;
	}
	if(!pilhaVazia(pilha)){
		continua = 0;
	}
	esvaziaPilha(pilha);
	free(pilha);
	if(continua == 0){
		return 0;
	}
	return 1;
}

/*INFIXA TO POSFIXA*/

int priorMaiorOuIgual(char atual,char c){
	if(atual == '*'||atual == '/'){
		if(c == '('||c == '+'||c == '-'){
			return 0;
		}
		return 1;
	}
	else if(atual == '+'||atual == '-'){
		if(c == '('){
			return 0;
		}
		return 1;
	}
	return 0;
}

int operador(char c){
	if(c == '*'||c == '/'||c == '+'||c == '-'||c == '('||c == ')'){
		return 1;
	}
	return 0;
}

char* convertePosfixa(char* infixa){
	t_pilha* pilha = criaPilha();
	char* posfixa = criaString(151);
	char desempilhado = '\0';
	int i = 0, j = 0, space = 1;
	while(infixa[i]!='\0'){
		if(operador(infixa[i])){
			if(space == 1){
				posfixa[j] = ' ';
				space = 0;
				j++;
			}
			if(infixa[i] == ')'){
				desempilhado = desempilhar(pilha);
				while(desempilhado != '('){
					posfixa[j] = desempilhado;
					desempilhado = desempilhar(pilha);
					j++;
				}
				desempilhado = '\0';
			}
			else{
				while(!pilhaVazia(pilha) && priorMaiorOuIgual(infixa[i],pilha->l->inicio->dado)){
					posfixa[j] = desempilhar(pilha);
					j++;
				}
				empilhar(infixa[i], pilha);
			}
		}
		else{
			posfixa[j] = infixa[i];
			space = 1;
			j++;
		}
		i++;
	}
	if(!operador(posfixa[j-1])){
		posfixa[j] = ' ';
		j++;
	}
	while(!pilhaVazia(pilha)){
		posfixa[j] = desempilhar(pilha);
		j++;
	}	
	posfixa[j] = '\0';
	esvaziaPilha(pilha);
	free(pilha);
	ajustaString(&posfixa);
	free(infixa);
	return posfixa;
}

/*End Fixa to Posfixa*/

/*AVALIA*/

int avaliaExpressao(char* posfixa){
	t_pilhaint* pilha = criaPilhaint();
	int i = 0, j = 0, num1, num2, result;
	char vetor[10];
	while(posfixa[i] != '\0'){
		if(!operador(posfixa[i])){
			while(posfixa[i] != ' ' && posfixa[i] != '\0'){
				vetor[j] = posfixa[i];
				j++;
				i++;
			}
			vetor[j] = '\0';
			num1 = atoi(vetor);
			empilharint(num1,pilha);
		}
		else{
			num1 = desempilharint(pilha);
			num2 = desempilharint(pilha);
			switch(posfixa[i]){
				case '+':
					result = num1 + num2;
				break;
				case '-':
					result = num2 - num1;
				break;
				case '*':
					result = num1 * num2;
				break;
				case '/':
					result = num2 / num1;
				break;
			}
			empilharint(result, pilha);
		}
		j = 0;
		i++;
	}
	result = desempilharint(pilha);
	esvaziaPilhaint(pilha);
	free(pilha);
	free(posfixa);
	return result;
}

/*End Avalia*/

int main(){
	char* expressao;
	int i = 0;
	expressao = leString();
	while(!valida(expressao)){
		printf("Expressao invalida. Informe outra expressao: \n");
		free(expressao);
		expressao = leString();
	} 
	expressao = convertePosfixa(expressao);
	while(expressao[i] != '\0'){
		printf("%c", expressao[i]);
		if(operador(expressao[i])){
			printf(" ");
		}
		i++;
	}
	printf("\n");
	printf("Resultado da operacao: %d\n", avaliaExpressao(expressao));
	return 0;
}

