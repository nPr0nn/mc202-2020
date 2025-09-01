#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

#include "stack.h"
#include "operacoes_string.h"
#include "planilha.h"

int main(){	
	char *caminho_para_o_arquivo;
	int colunas, linhas;
	scanf("%ms %d %d", &caminho_para_o_arquivo, &colunas, &linhas);
	FILE *ponteiro_para_arquivo = fopen(caminho_para_o_arquivo, "r");
	
	char operacao;
	char *novo_valor = malloc(MAX*sizeof(char));	
	char *coordenada = malloc(MAX*sizeof(char));
	strcpy(novo_valor, "");
	strcpy(coordenada, "");

	// Trata erros de arquivo
	if(ponteiro_para_arquivo == NULL){ printf("%s\n", "Arquivo Inexistente"), exit(0); }
	Planilha planilha = criar_planilha(colunas, linhas);

	//Entrada ~ Leitura dos dados do CSV
	Preencher_planilha_com_CSV(ponteiro_para_arquivo, planilha);

	// Processamento
	while(scanf("%c", &operacao) != EOF){
		switch(operacao){
			case 'G':
				scanf("%s", coordenada);
				leitura(planilha, coordenada, colunas, linhas);
				break;
			case 'S':
				scanf("%s", coordenada);
				scanf("%s", novo_valor);
				escrita(planilha, coordenada, novo_valor);
				break;
		}
	}

	// Liberar Memoria alocada
	free(caminho_para_o_arquivo);
	fclose(ponteiro_para_arquivo);
	destruir_planilha(planilha, colunas, linhas);
	free(planilha);
	free(novo_valor);
	free(coordenada);
}