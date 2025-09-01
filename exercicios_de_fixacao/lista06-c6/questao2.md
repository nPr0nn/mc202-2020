```c
#include <stdio.h>
#include <stdlib.h>

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

int main(){
	int dimensao, numero_p;
	scanf("%d %d", &dimensao, &numero_p);

	double soma_das_dist = 0;
	double *centroide = malloc(dimensao*sizeof(double));
	for(int j = 0; j < dimensao; j++) centroide[j] = 0;
	double **matriz = (double**) malloc(numero_p*dimensao*sizeof(double));

	for(int i = 0; i < numero_p; i++){
		matriz[i] = malloc(dimensao*sizeof(double));
		for(int j = 0; j < dimensao; j++){
			double coordenada;
			scanf("%lf", &coordenada);
			matriz[i][j] = coordenada;
			centroide[j] += coordenada;
		}
	}

	printf("%s\n","Centroide:");
	for(int j = 0; j < dimensao; j++){
		centroide[j] /= numero_p;
		double soma_de_quadrados = 0;
		for(int i = 0; i < numero_p; i++) soma_de_quadrados += (centroide[j] - matriz[i][j])*(centroide[j] - matriz[i][j]);
		soma_das_dist += RaizQuadrada(soma_de_quadrados);
		printf("%lf ", centroide[j]);
	}
	printf("\n");
	printf("%s\n", "Soma das Distancias");
	printf("%lf\n", soma_das_dist);

	free(centroide);
	for(int i = 0; i < numero_p; i++) free(matriz[i]);
	free(matriz);
}
```