#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Verifica se a posição verificada está fora dos limites
int seguro(int i, int j, int n_linhas, int n_colunas){
	if( (i >= 0) && (j >= 0) ){
		if( (i < n_linhas) && (j < n_colunas) ) return 1;
		return 0;
	}
	return 0;
}

int Busca_em_Profundidade(int n_linhas, int n_colunas, char **livro, char *palavra, int i, int j, int level){
	if(strlen(palavra) == level){
		return 1;
	}
	if(seguro(i, j, n_linhas, n_colunas) == 0) return 0;

	if(livro[i][j] == palavra[level]){
		int di[4] = {1, -1, 0, 0};
		int dj[4] = {0, 0, 1, -1};
		char temporario = livro[i][j];
		livro[i][j] = '#'; //Marca como posição visitada
		int res = 0;

		for(int k = 0; k < 4; k++){
			int pi = i + di[k];
			int pj = j + dj[k];
			res += Busca_em_Profundidade(n_linhas, n_colunas, livro, palavra, pi, pj, level+1);
		}
		livro[i][j] = temporario; //Desmarca como posição visitada
		if(res > 0) return 1;
	}
	return 0;
}

//Procura pela letra inicial e faz uma Busca em Profundidade para verificar se forma a palavra toda
int verifica_se_existe(int n_linhas, int n_colunas, char **livro, char *palavra){
	if(strlen(palavra) > n_linhas*n_colunas) return 0;
	for(int i = 0; i < n_linhas; i++){
		for(int j = 0; j < n_colunas; j++){
			if(livro[i][j] == palavra[0]){
				if(Busca_em_Profundidade(n_linhas, n_colunas, livro, palavra, i, j, 0)) return 1;
			}
		}
	}
	return 0;
}

int main(){
	int n_linhas, n_colunas, n_de_palavras;
	scanf("%d %d %d",&n_linhas, &n_colunas, &n_de_palavras);

	char **livro;
	livro = malloc(10*n_linhas*sizeof(char*));

	for(int i = 0; i < n_linhas; i++){
		livro[i] = malloc(10*n_colunas*sizeof(char));
		scanf("%s", livro[i]);
	}

	char *palavra;
	palavra = malloc(20*sizeof(char));
	for(int k = 0; k < n_de_palavras; k++){
		scanf("%s", palavra);
		if(verifica_se_existe(n_linhas, n_colunas, livro, palavra)) printf("%s\n", "sim");
		else printf("%s\n", "nao");
	}


	for(int i = 0; i < n_linhas; i++) free(livro[i]);
	free(palavra);
	free(livro);
}