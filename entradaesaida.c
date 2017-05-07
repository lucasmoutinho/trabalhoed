void entrada(){
	int i=0, continua=1, p=0;
	char expressao[20];
	printf ("Informe a expressao: ");
	scanf ("%s", expressao);
	while (p==0){
		while (expressao[i]!='\0' && continua==1){
			continua=valida(expressao[i]);
			i++;
		}
		p=1;
		if (continua==0){
			printf("expressao invalida. Informe outra expressao:");
			scanf ("%s", expressao);
			p==0;
		}
	}	
}