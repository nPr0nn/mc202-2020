#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TAD de uma Arvore Binaria de Busca Splay
typedef struct No{ 
    int dado;
    int quantidade;
    struct No *esq, *dir; 
}No;
typedef No *no_ponteiro; 
 
no_ponteiro criar_arvoreSplay(int dado) { 
    no_ponteiro no = malloc(sizeof(No)); 
    no->dado = dado; 
    no->quantidade = 1;
    no->esq = no->dir  = NULL; 
    return no; 
} 
 
//Funções de rotação na arvore Splay 
no_ponteiro rotacionar_dir(no_ponteiro x){ 
    no_ponteiro y = x->esq; 
    x->esq = y->dir; 
    y->dir = x; 
    return y; 
} 
no_ponteiro rotacionar_esq(no_ponteiro x) { 
    no_ponteiro y = x->dir; 
    x->dir = y->esq; 
    y->esq = x; 
    return y; 
} 
 
//Função splay que tenta levar o No buscado para Raiz
no_ponteiro splay(no_ponteiro raiz, int dado) { 
    if (raiz == NULL || raiz->dado == dado) return raiz;
    //Caso esquerda 
    if (raiz->dado > dado){ 
        if (raiz->esq == NULL) return raiz;   
        if (raiz->esq->dado > dado){ 
            raiz->esq->esq = splay(raiz->esq->esq, dado);   
            raiz = rotacionar_dir(raiz); 
        } 
        else if (raiz->esq->dado < dado){ 
            raiz->esq->dir = splay(raiz->esq->dir, dado); 
             if (raiz->esq->dir != NULL) raiz->esq = rotacionar_esq(raiz->esq); 
        } 
        if(raiz->esq == NULL) return raiz;
        else return rotacionar_dir(raiz);
    } 
    //Caso direita
    else{ 
        if (raiz->dir == NULL) return raiz;   
        if (raiz->dir->dado > dado){ 
            raiz->dir->esq = splay(raiz->dir->esq, dado);   
            if (raiz->dir->esq != NULL) raiz->dir = rotacionar_dir(raiz->dir); 
        } 
        else if (raiz->dir->dado < dado){ 
            raiz->dir->dir = splay(raiz->dir->dir, dado); 
            raiz = rotacionar_esq(raiz); 
        }   
        if(raiz->dir == NULL) return raiz;
        else return rotacionar_esq(raiz);
    } 
} 

no_ponteiro buscar_arvore(no_ponteiro raiz, int valor){
	raiz = splay(raiz, valor);	
	return raiz;
}

//Atualiza a contagem de um elemento
int acrescentar_arvore(no_ponteiro raiz, int valor){
	if(raiz == NULL) return 1; 
	if(raiz->dado == valor){
		raiz->quantidade += 1;
		return 0;
	}
	if(valor < raiz->dado) return acrescentar_arvore(raiz->esq, valor);
	else return acrescentar_arvore(raiz->dir, valor);
	return 1;
}

//Funções para inserir na arvore Splay sem repetir elementos
no_ponteiro inserir_real(no_ponteiro raiz, int k){ 
    if (raiz == NULL){
    	no_ponteiro novok = criar_arvoreSplay(k);
    	return novok;
    }   
    raiz = splay(raiz, k);   
    if (raiz->dado == k) return raiz; 
    no_ponteiro novo = criar_arvoreSplay(k); 
    if(raiz->dado > k){ 
        novo->dir = raiz; 
        novo->esq = raiz->esq; 
        raiz->esq = NULL; 
    } 
    else{ 
        novo->esq = raiz; 
        novo->dir = raiz->dir; 
        raiz->dir = NULL; 
    } 
    return novo;
}
no_ponteiro inserir(no_ponteiro raiz, int valor){
	int inserir = acrescentar_arvore(raiz, valor);
	if(inserir == 1) raiz = inserir_real(raiz, valor);
	return raiz;
}

//Conta elementos a serem retirados para se tornar uma lista legal
void processar_in_ordem(no_ponteiro raiz, int *meta){
	if(raiz != NULL){
		processar_in_ordem(raiz->esq, meta);
		int total = raiz->quantidade;
		int valor = raiz->dado;
		if(total < valor) *meta += (total);
		else if(total > valor) *meta += (total-valor);
		processar_in_ordem(raiz->dir, meta);
	}
}

void destruir_arvore(no_ponteiro raiz){
	if(raiz == NULL) return;
	destruir_arvore(raiz->esq);
	destruir_arvore(raiz->dir);
	free(raiz);
}


int main(){
	no_ponteiro arvoreSplay;
	int iniciar = 1;
	int quantidade_de_numeros_na_lista;
	int numero_de_operacoes;
	scanf("%d %d", &quantidade_de_numeros_na_lista, &numero_de_operacoes);

	//Entrada
	int meta;
	for(int i = 0; i < quantidade_de_numeros_na_lista; i++){
		int numero;
		scanf("%d", &numero);
		if(iniciar == 1){
			arvoreSplay = criar_arvoreSplay(numero);
			iniciar = 0;
		}
		else arvoreSplay = inserir(arvoreSplay, numero);
	}

	//Operações
	for(int i = 0; i < numero_de_operacoes; i++){
		int jj, m;
		int tipo_de_operacao;
		scanf("%d", &tipo_de_operacao);

		if(tipo_de_operacao == 1){
			scanf("%d", &jj);
			arvoreSplay = inserir(arvoreSplay, jj);
		}
		else if(tipo_de_operacao == 2){
			scanf("%d", &m);
			arvoreSplay = buscar_arvore(arvoreSplay, m);
			if(arvoreSplay->dado == m) printf("%d\n", arvoreSplay->quantidade);
			else printf("%d\n", 0);
		}
		else if(tipo_de_operacao == 3){
			meta = 0;
			processar_in_ordem(arvoreSplay, &meta);
			printf("%d\n", meta);
		}
	}

	destruir_arvore(arvoreSplay);
}