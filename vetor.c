#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* criaVetor(int n){
	char* vetor = (char*)malloc(n*sizeof(char));
	return vetor;
}

int main(){
	char* infixa;
	int i = 0;
	infixa = criaVetor(151);
	scanf("%s", infixa);
  	infixa = (char*)realloc(infixa,(((int)strlen(infixa)+1)*sizeof(char)));
  	printf("%d\n", (int)strlen(infixa));
  	while(infixa[i] != '\0'){
  		printf("%c ", infixa[i]);
  		i++;
  	}
	return 0;
}

