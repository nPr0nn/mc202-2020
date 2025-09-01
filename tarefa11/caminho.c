#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

#define teto(n) ((n-(int)(n)) > 0 ? (int)(n+1) : (int)(n))
#define oo 0x3f3f3f3f
#define epsilon 0.000001

//TAD de um ponto em R2
typedef struct ponto{
	double x;
	double y;
	char destino[10];
}ponto;

// Maximo entre dois decimais a e b
double max(double a, double b){
	if((a-b)>epsilon) return a;
	return b;
}

// Minimo entre dois inteiros a e b
int min(int a, int b){
	if(a > b) return b;
	return a;
}

// Raiz Quadrada pelo metodo de Newton
double RaizQuadrada(double n){
	double x = n;
	double precisao = 0.00001;
	double raiz;
	int contador = 0;
	while(1){
		contador++;
		raiz = 0.5*(x + (n/x));
		if(abs(raiz - x) < precisao) break;
		x = raiz;
	}
	return raiz;
}

// Distancia Euclidiana
double distancia(ponto a, ponto b){
	double d = (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
	return RaizQuadrada(d);
}

// Busca em Profundidade
int dfs(grafo_ponteiro grafo, int atual, int destino, int *vis, double limite){
	vis[atual] = 1;	
	int resposta = 0;
	if(atual == destino) return 1;

	no_ponteiro lista;
	for(lista = grafo->adjacencia[atual]; lista != NULL; lista = lista->prox){
		if(vis[lista->valor] == 0 && (lista->peso <= limite)){
			if(!resposta) resposta = dfs(grafo, lista->valor, destino, vis, limite);
		}
	}
	return resposta;
}

int main(){
	double x_red, y_red;
	int qtd_de_vertices = 0;
	int qtd_de_lugias = 0;
	double maior_aresta = 0;
	scanf("%lf %lf", &x_red, &y_red);

	//Entrada de dados
	ponto *pontos = malloc(2*sizeof(ponto));
	double x, y;
	char *destino = malloc(10*sizeof(char));;
	while(1){
		if(scanf("%lf", &x) == EOF) break;
		scanf("%lf", &y);
		scanf("%s", destino);
		qtd_de_vertices++;
		pontos[qtd_de_vertices].x = x;
		pontos[qtd_de_vertices].y = y;
		strcpy(pontos[qtd_de_vertices].destino, destino);
		pontos = realloc(pontos, (qtd_de_vertices+2)*sizeof(ponto));
	}
	strcpy(pontos[0].destino, "origem");
	pontos[0].x = x_red;
	pontos[0].y = y_red;

	int *lugias = malloc(qtd_de_vertices*sizeof(int));
	grafo_ponteiro grafo = criar_grafo(3*qtd_de_vertices);
	
	//Constroi o Grafo com pesos
	for(int i = 0; i <= qtd_de_vertices; i++){
		if(strcmp(pontos[i].destino, "Lugia") == 0){lugias[qtd_de_lugias] = i, qtd_de_lugias++;}
		for(int j = 0; j <= qtd_de_vertices; j++){
			if(i != j){
				double dist = distancia(pontos[i], pontos[j]);
				criar_aresta(grafo, i, j, dist);
				maior_aresta = max(maior_aresta, dist);
			}
		}
	}

	int *visitados = malloc(2*qtd_de_vertices*sizeof(int));

	int vertice_lugia;
	int resposta_global = oo;
	int resposta_local = oo;
	
	int sucesso;
	int sucesso_anterior;

	for(int i = 0; i < qtd_de_lugias; i++){
		vertice_lugia = lugias[i];
		
		int ini = 0;
		int fim = teto(maior_aresta);

		// Busca Binaria para a achar o valor minimo válido
		while(ini <= fim){
			int mid = (ini + fim)/2;
			memset(visitados, 0, 2*qtd_de_vertices*sizeof(int));
			sucesso = dfs(grafo, 0, vertice_lugia, visitados, mid);
			memset(visitados, 0, 2*qtd_de_vertices*sizeof(int));
			sucesso_anterior = dfs(grafo, 0, vertice_lugia, visitados, mid-1);

			if(sucesso == 1 && sucesso_anterior == 0){
				resposta_local = mid;
				break;
			}
			else if(sucesso == 1 && sucesso_anterior == 1) fim = mid-1;
			else ini = mid+1;
		}

		resposta_global = min(resposta_local, resposta_global);
	}
	printf("%d\n", resposta_global);

	free(visitados);
	free(lugias);
	free(pontos);
	free(destino);
	destruir_grafo(grafo);
}