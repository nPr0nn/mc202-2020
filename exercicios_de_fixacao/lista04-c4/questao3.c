#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Todas as cores 0 significa branco 
typedef struct{
	char nome[10];
	int corBase[5];
}cor;

typedef struct {
	int tam;
	cor paleta[10000];
}Paleta;

Paleta iniciar_paleta(Paleta cores){
	char tintas[5][10] = {"azul","amarelo","vermelho","preto","branco"};
	cores.tam = 5;
	for(int i=0; i < 5; i++){
		for(int l=0; l< 5; l++){
			if(i == l) cores.paleta[i].corBase[l] = 100;
			else cores.paleta[i].corBase[l] = 0;
		}
		// printf("%s\n", c);
		strcpy(cores.paleta[i].nome, tintas[i]);
	}
	return cores;
}

void printar_cor(cor c){
	printf("%s\n", c.nome);
	for(int i = 0; i < 5; i++) printf("%d ", c.corBase[i]);
}

void printar_paleta(Paleta *cores){
	const char *tintas[5] = {"azul", "amarelo", "vermelho", "preto", "branco"};
	for(int i =0; i < cores->tam; i++){
		printf("%d %s ", i, cores->paleta[i].nome);
		printf("%s \n", ": ");
		for (int l = 0; l < 5; l++){
			printf("%s %c %d %s \n", tintas[l], '(', cores->paleta[i].corBase[l], "%)");
		}
		printf("\n");
	}
}

cor misturar_cores(){
	const char *tintas[5] = {"azul", "amarelo", "vermelho", "preto", "branco"};
	Paleta cores;
	cores = iniciar_paleta(cores);
	printf("%s\n", "Escolha duas cores pelos números");
	printar_paleta(&cores);

	int a,b;
	scanf("%d %d", &a, &b);
	
	cor res;
	printf("%s\n", "Escolha um nome para sua nova cor");

	char c[50];
	scanf("%s", c);
	strcpy(res.nome, c);
	
	for(int i =0; i<3; i++){
		res.corBase[i] = cores.paleta[a].corBase[i] + cores.paleta[b].corBase[i];
	}
	if(cores.paleta[a].corBase[3] > 0 || cores.paleta[b].corBase[3] > 0){
		res.corBase[3] = 100;
		for(int i =0; i<3; i++) if(i !=3) res.corBase[i] = 0;
	}

	int total = 0;
	for(int i=0; i < 5; i++) total += res.corBase[i];
	for(int i=0; i < 5; i++) res.corBase[i] = (res.corBase[i]*100)/total;
	return res;
}

int main(){
	cor c;
	c = misturar_cores();
	// printf("\n");
	printar_cor(c);
}