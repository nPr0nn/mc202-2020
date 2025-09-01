#include <stdio.h>

int main(){
	int numero_de_nomes;
	scanf("%d", &numero_de_nomes);
	while(numero_de_nomes--){
		char nome[100];
		scanf("%s", nome);
		printf("Boa noite, %s.\n", nome);
	}
}