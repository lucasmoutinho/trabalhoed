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

/*Structs com reais*/

typedef struct elementofloat{
	float dado;
	struct elementofloat* proximo;
} t_elementofloat;

typedef struct listafloat{
	t_elementofloat* inicio;
	t_elementofloat* fim;
} t_listafloat;

typedef struct pilhafloat{
	t_listafloat* l;
}t_pilhafloat;

typedef struct filafloat{
	t_listafloat* l;
}t_filafloat;

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

/*ALGORITMOS COM PILHA float*/

t_listafloat* criaListafloat(){
	t_listafloat* l = (t_listafloat*)malloc(sizeof(t_listafloat));
	l->inicio=NULL;
	l->fim=NULL;
	return l;
}

void insereIniciofloat(float valor, t_listafloat* l){
	t_elementofloat* nv;
	nv = (t_elementofloat*)malloc(sizeof(t_elementofloat)); 
	nv->dado = valor;
	nv->proximo = l->inicio;
	l->inicio = nv;
	if(l->fim == NULL){
		l->fim = nv;
	}
}

float estaVaziafloat(t_listafloat* l){
	if(l->inicio == NULL){
		return 1;
	}
	return 0;
}

float removeIniciofloat(t_listafloat* l){
	if(estaVaziafloat(l)){
		return '\0';
	}
	t_elementofloat* p = l->inicio;
	l->inicio = p->proximo;
	float tmp = p->dado;
	free(p);
	if(l->inicio == NULL){
		l->fim = NULL;
	}
	return tmp;
}

t_pilhafloat* criaPilhafloat(){
	t_pilhafloat* p = (t_pilhafloat*)malloc(sizeof(t_pilhafloat));
	p->l = criaListafloat();
	return p;
}

void empilharfloat(float valor, t_pilhafloat* p){
	insereIniciofloat(valor, p->l);
}

float desempilharfloat(t_pilhafloat* p){
	return removeIniciofloat(p->l);
}

void esvaziaPilhafloat(t_pilhafloat*p){
	while(p->l->inicio != NULL){
		removeIniciofloat(p->l);
	}
}

/*ALGORITMOS COM PILHA float*/

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

int validaInfixa(char* infixa){
	int i = 0, continua;
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
				desempilhar(pilha);
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
	char* posfixa = criaString(201);
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

float avaliaExpressao(char* posfixa){
	t_pilhafloat* pilha = criaPilhafloat();
	int i = 0, j = 0, num;
	float result, num1, num2;
	char vetor[10];
	while(posfixa[i] != '\0'){
		if(!operador(posfixa[i])){
			while(posfixa[i] != ' ' && posfixa[i] != '\0'){
				vetor[j] = posfixa[i];
				j++;
				i++;
			}
			vetor[j] = '\0';
			num = atoi(vetor);
			num1 = ((float)num);
			empilharfloat(num1,pilha);
		}
		else{
			num1 = desempilharfloat(pilha);
			num2 = desempilharfloat(pilha);
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
			empilharfloat(result, pilha);
		}
		j = 0;
		i++;
	}
	result = desempilharfloat(pilha);
	esvaziaPilhafloat(pilha);
	free(pilha);
	free(posfixa);
	return result;
}

/*End Avalia*/

int main(){
	char* expressao;
	int i = 0;
	printf("Informe uma expressao aritmetica em sua forma infixa:\n");
	expressao = leString();
	while(!validaInfixa(expressao)){
		printf("Expressao invalida. Informe outra expressao: \n");
		free(expressao);
		expressao = leString();
	} 
	expressao = convertePosfixa(expressao);
	printf("Expressao em sua forma posfixa:\n");
	while(expressao[i] != '\0'){
		printf("%c", expressao[i]);
		if(operador(expressao[i])){
			printf(" ");
		}
		i++;
	}
	printf("\n");
	printf("Resultado da expressao aritmetica: %.2f\n", avaliaExpressao(expressao));
	printf("Pressione ENTER para finalizar\n");
	getchar();
	return 0;
}

