#include <stdio.h>
#include "professor_carlos.h"

void Entrada_dos_dados_das_Turmas(Turma *T, int numero_de_turmas){
	for(int i = 0; i < numero_de_turmas; i++){
		int quantos_alunos;
		scanf("%d", &quantos_alunos);
		T[i].qtd = quantos_alunos;

		for(int j = 0; j < quantos_alunos; j++){
			Data D;
			Aluno A;
			scanf("%s", A.nome);
			scanf("%s", A.sobrenome);
			scanf("%d", &D.dia);
			scanf("%d", &D.mes);
			scanf("%d", &D.ano);
			A.nascimento = D;
			T[i].alunos[j] = A;
		}
	}
}

void Saida_das_respostas_das_operacoes(Turma *T, int numero_de_turmas, int numero_de_operacoes){
	for(int i = 0; i < numero_de_operacoes; i++){
		int x, j;
		int qtd;
		scanf("%d", &x);
		switch(x){
			case 1: ;
				scanf("%d", &j);
				Aluno mais_novo = procura_novo_na_turma(T, numero_de_turmas, j);
				printf("%s\n", mais_novo.nome);
				break;
			case 2: ;
				scanf("%d", &j);
				Aluno mais_velho = procura_velho_na_turma(T, numero_de_turmas, j);
				printf("%s\n", mais_velho.sobrenome);
				break;
			case 3: ;
				Aluno mais_velho2 = procura_velho_todas_turmas(T, numero_de_turmas);
				printf("%s\n", mais_velho2.nome);
				break;
			case 4: ;
				Aluno mais_novo2 = procura_novo_todas_turmas(T, numero_de_turmas);
				printf("%s\n", mais_novo2.sobrenome);
				break;
			case 5: ;
				char padrao[16];
				scanf("%s", padrao);
				qtd = conta_substrings(T, numero_de_turmas, padrao);
				printf("%d\n", qtd);
				break;
			case 6: ;
				Data D;
				Aluno A;
				scanf("%d", &j);
				scanf("%s", A.nome);
				scanf("%s", A.sobrenome);
				scanf("%d", &D.dia);
				scanf("%d", &D.mes);
				scanf("%d", &D.ano);
				A.nascimento = D;
				qtd = add_aluno(T, A, j);
				printf("%d\n", qtd);
				break;
			case 7: ;
				scanf("%d", &j);
				qtd = remove_aluno(T, j);
				printf("%d\n", qtd);
				break;
		}
	}
}

int main(){
	int numero_de_turmas, numero_de_operacoes;
	scanf("%d %d ", &numero_de_turmas, &numero_de_operacoes);

	Turma T[51];
	Entrada_dos_dados_das_Turmas(T, numero_de_turmas);
	Saida_das_respostas_das_operacoes(T, numero_de_turmas, numero_de_operacoes);
}
