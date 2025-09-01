#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Busca Binaria para encontrar a raiz de um numero
double raizQuadrada(double numero, int precisao){ 
    int inicio = 0, fim = numero; 
    int meio; 
    double raiz; 
    while (inicio <= fim) { 
        meio = (inicio+fim) / 2; 
        if (meio*meio == numero) { 
            raiz = meio; 
            break; 
        } 
        else if(meio*meio < numero){
        	inicio = meio + 1;
        	raiz = meio;
        }
        else fim = meio - 1; 
    } 
    double dx = 0.1; 
    for (int i = 0; i < precisao; i++) { 
        while (raiz*raiz <= numero) raiz += dx; 
        raiz -= dx; 
        dx /= 10; 
    } 
    return raiz; 
} 

double tirar_a_media(double *relevancia, int quantidade_de_dias_no_historico){
	double media = 0;
	for(int i = 0; i < quantidade_de_dias_no_historico; i++){
		media += *(relevancia+i);
	}
	return media/quantidade_de_dias_no_historico;
}

double tirar_a_desvio_padrao(double *relevancia, double media, int quantidade_de_dias_no_historico){
	double desvio_padrao = 0;
	for(int i = 0; i < quantidade_de_dias_no_historico; i++){
		desvio_padrao += (*(relevancia+i)- media)*(*(relevancia+i)-media);
	}
	desvio_padrao /=quantidade_de_dias_no_historico;
	double aux = raizQuadrada(desvio_padrao, 6);
	return aux;
}

double max(double *relevancia, int quantidade_de_dias_no_historico){
	double maximo = 0;
	for(int j = 0; j < quantidade_de_dias_no_historico; j++){
		if(*(relevancia+j) > maximo) maximo = *(relevancia+j);
	}
	return maximo;
}

double min(double *relevancia, int quantidade_de_dias_no_historico){
	double minimo = 100;
	for(int j = 0; j < quantidade_de_dias_no_historico; j++){
		if(*(relevancia+j) < minimo) minimo = *(relevancia+j);
	}
	return minimo;
}

int main(){
	int numero_de_termos_extraidos;
	int quantidade_de_dias_no_historico;

	scanf("%d%d", &numero_de_termos_extraidos, &quantidade_de_dias_no_historico);
	
	int *qtd;
	qtd = malloc(5*sizeof(int));
	for(int ii=0; ii<5; ii++) qtd[ii] = 0;

	char *bot = malloc(numero_de_termos_extraidos*25*sizeof(char));
	char *surpreendente = malloc(numero_de_termos_extraidos*25*sizeof(char));
	char *local = malloc(numero_de_termos_extraidos*25*sizeof(char));	
	char *normal = malloc(numero_de_termos_extraidos*25*sizeof(char));
	char *irrelevante = malloc(numero_de_termos_extraidos*25*sizeof(char));

	strcpy(bot, "");
	strcpy(surpreendente, "");
	strcpy(local, "");
	strcpy(normal, "");
	strcpy(irrelevante, "");

	double maximo, minimo, media, desvio_padrao;
	
	double *relevancia = malloc(quantidade_de_dias_no_historico*sizeof(double));
	char *termo = malloc(25*sizeof(char));
	
	for(int ii = 0; ii < numero_de_termos_extraidos; ii++){
		scanf("%s", termo);

		for(int j = 0; j < quantidade_de_dias_no_historico; j++) scanf("%lf", (relevancia+j));
		maximo = max(relevancia, quantidade_de_dias_no_historico);
		minimo = min(relevancia, quantidade_de_dias_no_historico);
		media = tirar_a_media(relevancia, quantidade_de_dias_no_historico);	
		desvio_padrao = tirar_a_desvio_padrao(relevancia, media, quantidade_de_dias_no_historico);
		
		printf("%s %.2lf %.2lf %.2lf %.2lf\n",termo, maximo, minimo, media, desvio_padrao);

		strcat(termo, " ");
		if(media >= 60 && desvio_padrao > 15) strcat(bot, termo), *(qtd+0) += 1;
		else if(media >= 60 && desvio_padrao <= 15) strcat(surpreendente, termo), *(qtd+1) += 1;
		else if(media < 60 && maximo >= 80 && minimo > 20) strcat(normal, termo), *(qtd+2) += 1;
		else if(media < 60 && maximo >= 80 && minimo <= 20) strcat(local, termo), *(qtd+3) += 1;
		else if(media < 60 && maximo < 80) strcat(irrelevante, termo), *(qtd+4) += 1;
		
	}
	free(termo);
	free(relevancia);

	printf("\n%s\n", "RESULTADO:");
	printf("%s%d%s%s\n", "Bot (", qtd[0],"): ",bot);
	printf("%s%d%s%s\n", "Surpreendente (", qtd[1], "): ", surpreendente);
	printf("%s%d%s%s\n", "Normal (", qtd[2], "): ", normal);
	printf("%s%d%s%s\n", "Local (", qtd[3], "): ", local);
	printf("%s%d%s%s\n", "Irrelevante (", qtd[4], "): ", irrelevante);

	free(qtd);
	free(bot);
	free(surpreendente);
	free(normal);
	free(local);
	free(irrelevante);
}