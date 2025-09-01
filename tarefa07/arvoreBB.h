//TAD Token
typedef struct papel{
	int numero;
	char texto[1000];
}papel;

// TAD de uma Arvore Binaria de Busca
typedef struct No{
	papel dado;
	struct No *dir, *esq, *pai;
}No;
typedef No *no_ponteiro;

//Funções auxiliares para Arvore Binaria de Busca
no_ponteiro ancestral_a_direita(no_ponteiro x){
	if(x == NULL) return NULL;
	if(x->pai == NULL || x->pai->esq == x) return x->pai;
	else ancestral_a_direita(x->pai);
	return NULL;
}
no_ponteiro ancestral_a_esquerda(no_ponteiro x){
	if(x == NULL) return NULL;
	if(x->pai == NULL || x->pai->dir == x) return x->pai;
	else ancestral_a_esquerda(x->pai);
	return NULL;
}
//Funções principais para Arvore Binaria de Busca
no_ponteiro criar_arvore(papel token){
	no_ponteiro raiz = malloc(sizeof(No));
	raiz->dado = token;
	raiz->esq = raiz->dir = NULL;
	raiz->pai = NULL;
	return raiz;
}
no_ponteiro inserir_arvore(no_ponteiro raiz, no_ponteiro pai, papel token){
	no_ponteiro novo;
	if(raiz == NULL){
		novo = malloc(sizeof(No));
		novo->dir = novo->esq = NULL;
		novo->dado = token;
		novo->pai = raiz;
		return novo;
	}
	if(token.numero < raiz->dado.numero) raiz->esq = inserir_arvore(raiz->esq, raiz, token);
	else if(token.numero > raiz->dado.numero) raiz->dir = inserir_arvore(raiz->dir, raiz, token);
	return raiz;
}
no_ponteiro buscar_arvore(no_ponteiro raiz, int token){
	if(raiz == NULL || raiz->dado.numero == token) return raiz;
	if(token < raiz->dado.numero) return buscar_arvore(raiz->esq, token);
	else return buscar_arvore(raiz->dir, token);
}
no_ponteiro minimo_arvore(no_ponteiro raiz){
	if(raiz == NULL || raiz->esq == NULL) return raiz;
	return minimo_arvore(raiz->esq);
}
no_ponteiro maximo_arvore(no_ponteiro raiz){
	if(raiz == NULL || raiz->dir == NULL) return raiz;
	return maximo_arvore(raiz->dir);
}
no_ponteiro sucessor_arvore(no_ponteiro x){
	if(x->dir != NULL) return minimo_arvore(x->dir);
	else return ancestral_a_direita(x);
}
no_ponteiro antecessor_arvore(no_ponteiro x){
	if(x->esq != NULL) return maximo_arvore(x->esq);
	else return ancestral_a_esquerda(x);
}
no_ponteiro retirar_arvore(no_ponteiro raiz, int valor){
	if(raiz == NULL) return raiz;
	if(valor < raiz->dado.numero) raiz->esq = retirar_arvore(raiz->esq, valor);
	else if(valor > raiz->dado.numero) raiz->dir = retirar_arvore(raiz->dir, valor);
    else{
        if(raiz->esq == NULL && raiz->dir == NULL){  
            free(raiz);
            return NULL;
        }
        else if(raiz->esq == NULL){
            no_ponteiro temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if(raiz->dir == NULL){        
            no_ponteiro temp = raiz->esq;
            free(raiz);
            return temp;
        }
        else{
            no_ponteiro min_dir = minimo_arvore(raiz->dir);
            raiz->dado = min_dir->dado;
            raiz->dir = retirar_arvore(raiz->dir,min_dir->dado.numero);
        }
    }
    return raiz;
}
void destuir_arvore(no_ponteiro raiz){
	if(raiz == NULL) return;
	destuir_arvore(raiz->esq);
	destuir_arvore(raiz->dir);
	free(raiz);
}

//Funções de Percorre Arvores
void print_in_ordem(no_ponteiro raiz){
	if(raiz != NULL){
		print_in_ordem(raiz->esq);
		// if(raiz->dado.numero != 0) printf("%s", raiz->dado.texto);
		printf("%s %d\n", raiz->dado.texto, raiz->dado.numero);
		print_in_ordem(raiz->dir);
	}
}

void print_in_ordem2(no_ponteiro raiz){
	if(raiz != NULL){
		print_in_ordem2(raiz->esq);
		if(raiz->dado.numero != 0) printf("%s", raiz->dado.texto);
		print_in_ordem2(raiz->dir);
	}
}