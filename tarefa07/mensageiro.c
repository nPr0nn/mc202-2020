#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreBB.h"

//Pega os dados da arvore em ordem crescente
void in_ordem(no_ponteiro raiz, int *ordem, int *quantidade_de_numeros, int id_da_autoridade){
	if(raiz != NULL){
		in_ordem(raiz->esq, ordem, quantidade_de_numeros, id_da_autoridade);
		if(raiz->dado.numero >= id_da_autoridade) return;
		*(ordem + (*quantidade_de_numeros)) = raiz->dado.numero;
		(*quantidade_de_numeros)++;
		in_ordem(raiz->dir, ordem, quantidade_de_numeros, id_da_autoridade);
	}
}

//Encontrar Nós a, b, c tal que a+b+c = k e atualizar a arvore
void resolver(no_ponteiro raiz, int id_da_autoridade){
	int *ordem = malloc(1000*sizeof(char));
	int quantidade_de_numeros = 0;
	in_ordem(raiz, ordem, &quantidade_de_numeros, id_da_autoridade);

	for(int i = 0; i < quantidade_de_numeros-2; i++){
		for(int inicio = i+1; inicio < quantidade_de_numeros-1; inicio++){
			for(int final = inicio+1; final < quantidade_de_numeros; final++){
				int soma = *(ordem+i) + *(ordem+inicio) + *(ordem+final);
				if(soma == id_da_autoridade && *(ordem+i) != 0){
					papel autoridade;
					autoridade.numero = id_da_autoridade;
					strcpy(autoridade.texto, "");

					no_ponteiro a = buscar_arvore(raiz, *(ordem+i));
					no_ponteiro b = buscar_arvore(raiz, *(ordem+inicio));
					no_ponteiro c = buscar_arvore(raiz, *(ordem+final));

					strcat(autoridade.texto, a->dado.texto);
					strcat(autoridade.texto, b->dado.texto);
					strcat(autoridade.texto, c->dado.texto);
					raiz = retirar_arvore(raiz, *(ordem+i));
					raiz = retirar_arvore(raiz, *(ordem+inicio));
					raiz = retirar_arvore(raiz, *(ordem+final));
					
					raiz = inserir_arvore(raiz, raiz->pai, autoridade);
					free(ordem);		
					return;	
				}
			}
		}
	}
	
	free(ordem);
	return;
}

int main(){
	int numero_cartoes, numero_autoridades;
	no_ponteiro arvoreBB;
	while(1){
		papel token;
		token.numero = 0;
		strcpy(token.texto, "Raiz");
		arvoreBB = criar_arvore(token);

		if(scanf("%d", &numero_cartoes) == EOF)break;
		scanf("%d", &numero_autoridades);		
		scanf("%*c");
		for(int i = 0; i < numero_cartoes; i++){
			scanf("%d", &token.numero);
			scanf("%*c");
			scanf("%*c");
			scanf("%[^\"]", token.texto);
			scanf("%*c");
			arvoreBB = inserir_arvore(arvoreBB, arvoreBB->pai, token);
		}

		for(int i = 0; i < numero_autoridades; i++){
			int id_da_autoridade;
			scanf("%d", &id_da_autoridade);
			resolver(arvoreBB, id_da_autoridade);
		}

		print_in_ordem2(arvoreBB);
		printf("\n");
		destuir_arvore(arvoreBB);
	}
	destuir_arvore(arvoreBB);
}