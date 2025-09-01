#include <stdio.h>

//Estrutura auxiliar para guard
struct marcado{
	int apostador;
	int indice;
};

//Retorna um ponteiro apontando para a lista de dinheiro arrecadado por cada apostador
double *dinheiro_dos_ganhadores(double *dinheiro, double premio, int total_de_acertos, int total_de_apostadores, struct marcado numeros_marcados[], int numeros_sorteados[]){
	int i, j;
	int acertos[1010];
	double faixa[4] = {0, 0, 0, 0};

	for(i = 0; i < total_de_apostadores; i++){
		acertos[i] = 0;
		dinheiro[i] = 0;
	}

	for(i = 0; i < total_de_acertos; i++){
		int apostador = numeros_marcados[i].apostador;
		int indice = numeros_marcados[i].indice;

		for(j = 0; j < 6; j++){
			if(indice == numeros_sorteados[j]){
				acertos[apostador]++;
			}
		}
	}

	for(i = 0; i < total_de_apostadores; i++){
		if(acertos[i] == 6) faixa[1]++;
		else if(acertos[i] == 5) faixa[2]++;
		else if(acertos[i] == 4) faixa[3]++;
	}


	for(i = 0; i < total_de_apostadores; i++){
		if(acertos[i] == 6){
			dinheiro[i] = ((premio*0.62)/faixa[1]);
		}
		else if(acertos[i] == 5){
			dinheiro[i] = ((premio*0.19)/faixa[2]);
		}
		else if(acertos[i] == 4){
			dinheiro[i] = ((premio*0.19)/faixa[3]);
		}
	}

	return dinheiro;
}

int main(){
	int total_de_apostadores, numeros_sorteados[6];
	double premio;
	int apostador, total_de_acertos;
	int j, k, marcou; // Variáveis auxiliares

	scanf("%d", &total_de_apostadores);
	scanf("%lf", &premio);
	struct marcado numeros_marcados[15*1010];
	
	total_de_acertos = 0;

	// Salva todas as informações sobre acertos em cartelas (indice e apostador)
	for(apostador = 0; apostador < total_de_apostadores; apostador++){
		int indice_da_cartela = 1;

		//Percorre uma cartela
		for(j = 0; j < 6; j++){
			for(k = 0; k < 10; k++){
				scanf("%d", &marcou);		
				if(marcou == 1){
					numeros_marcados[total_de_acertos].apostador = apostador;
					numeros_marcados[total_de_acertos].indice = indice_da_cartela;
					total_de_acertos++;
				}
				indice_da_cartela++;				
			}
		}
	}

	for(j = 0; j < 6; j++){
		scanf("%d", &numeros_sorteados[j]);
	}

	double ganhadores[1010];
	double *dinheiro = dinheiro_dos_ganhadores(ganhadores, premio, total_de_acertos, total_de_apostadores, numeros_marcados, numeros_sorteados);

	for(int i = 0; i < total_de_apostadores; i++){
		printf("%.2lf\n", dinheiro[i]);
	}
}