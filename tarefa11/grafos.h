//Grafos - Lista de Adjacencia
typedef struct No{
	int valor;
	double peso;
	struct No *prox; 
}No;
typedef No * no_ponteiro;

// TAD para lista de adjacencia
typedef struct Grafo{
	no_ponteiro *adjacencia;
	int tamanho;
} Grafo;
typedef Grafo * grafo_ponteiro;

grafo_ponteiro criar_grafo(int tamanho){
	grafo_ponteiro grafo = malloc(sizeof(Grafo));
	grafo->tamanho = tamanho/2;
	grafo->adjacencia = malloc((tamanho/2)*sizeof(no_ponteiro));
	for(int i = 0; i < tamanho/2; i++){
		grafo->adjacencia[i] = NULL;
	}
	return grafo;
}

//Apagar Grafo
void liberar_lista(no_ponteiro no){
	if(no != NULL){
		liberar_lista(no->prox);
		free(no);
	}
}
void destruir_grafo(grafo_ponteiro grafo){
	for(int i = 0; i < grafo->tamanho; i++){
		liberar_lista(grafo->adjacencia[i]);
	}
	free(grafo->adjacencia);
	free(grafo);
}

//Operações nas Arestas
no_ponteiro inserir_na_lista(no_ponteiro lista, int x, double peso){
	no_ponteiro novo = malloc(sizeof(No));
	novo->valor = x;
	novo->peso = peso;
	novo->prox = lista;
	return novo;
}

void criar_aresta(grafo_ponteiro grafo, int x, int y, double peso){
	grafo->adjacencia[x] = inserir_na_lista(grafo->adjacencia[x], y, peso);
}

no_ponteiro deletar_da_lista(no_ponteiro lista, int x){
	no_ponteiro proximo;
	if(lista == NULL) return NULL;
	else if(lista->valor == x){
		proximo = lista->prox;
		free(lista);
		return proximo;
	}
	else{
		lista->prox = deletar_da_lista(lista->prox, x);
		return lista;
	}
}

// Verificando e imprimindo
int verificar_aresta(grafo_ponteiro grafo, int x, int y){
	no_ponteiro lista;
	for(lista = grafo->adjacencia[x]; lista != NULL; lista = lista->prox){
		if(lista->valor == y) return 1;
	}
	return 0;
}
void imprimir_arestas(grafo_ponteiro grafo){
	no_ponteiro lista;
	for(int i = 0; i < 1; i++){
		printf("%s%d%s \n", "Distancias dos vizinho ao vertice ",i, ": ");
		for(lista = grafo->adjacencia[i]; lista != NULL; lista = lista->prox){
			printf("%d %lf \n", lista->valor, lista->peso);
		}
		printf("\n");
	}
}

