#include "professor_carlos.h"

//Compara a ordem lexicográfica
int compara(char a[], char b[]){
	int i = 0;
	while(a[i] == b[i] && a[i] != '\0') i++;

	if(a[i] < b[i]) return 1;
	else if(a[i] > b[i]) return -1;
	return 0;
}

//Verifica se o Aluno a é mais novo que o Aluno b 
int primeiro_mais_novo(Aluno a, Aluno b){
	if(a.nascimento.ano == b.nascimento.ano){
		if(a.nascimento.mes == b.nascimento.mes){
			if(a.nascimento.dia == b.nascimento.dia){
				if(compara(a.nome, b.nome) == 0){
					if(compara(a.sobrenome, b.sobrenome) > 0) return 1;
					else return 0;
				}
				else{
					if(compara(a.nome, b.nome) > 0) return 1;
					else return 0;
				}
			}
			return a.nascimento.dia > b.nascimento.dia;
		}
		return a.nascimento.mes > b.nascimento.mes;
	}
	return a.nascimento.ano > b.nascimento.ano;
}

//Verifica se o Aluno a é mais velho que o Aluno b 
int primeiro_mais_velho(Aluno a, Aluno b){
	if(a.nascimento.ano == b.nascimento.ano){
		if(a.nascimento.mes == b.nascimento.mes){
			if(a.nascimento.dia == b.nascimento.dia){
				if(compara(a.nome, b.nome) == 0){
					if(compara(a.sobrenome, b.sobrenome) < 0) return 1;
					else return 0;
				}
				else{
					if(compara(a.nome, b.nome) < 0) return 1;
					else return 0;
				}
			}
			return a.nascimento.dia > b.nascimento.dia;
		}
		return a.nascimento.mes > b.nascimento.mes;
	}
	return a.nascimento.ano > b.nascimento.ano;
}

//Verifica se a string nome contem a string padrao
int contem(char *nome, char *padrao){
	char *aux;
	char *aux2;

	aux = nome;
	aux2 = padrao;
	int sim = 0;

	while(*aux != '\0'){
		aux = nome;
		aux2 = padrao;
		while(*aux2 != '\0'){
			if(*aux == *aux2){
				aux++;
				aux2++;
				sim = 1;
			}
			else{
				sim = 0;
				break;
			}
		}
		if(sim) break;
		nome++;
	}
	return sim;
}

Aluno procura_novo_na_turma(Turma T[], int qtd_turmas, int j){
	Aluno mais_novo = T[j].alunos[0];
	for(int i = 1; i < T[j].qtd; i++){
		if(primeiro_mais_novo(T[j].alunos[i], mais_novo) == 1){
			mais_novo = T[j].alunos[i];
			// printf("%s\n",mais_novo.nome);
		}
	}
	return mais_novo;
}

Aluno procura_novo_todas_turmas(Turma T[], int qtd_turmas){
	Aluno mais_novo_local;
	Aluno mais_novo_global = T[0].alunos[0];
	for(int i = 0; i < qtd_turmas; i++){
		mais_novo_local = procura_novo_na_turma(T, qtd_turmas, i);
		if(primeiro_mais_novo(mais_novo_local, mais_novo_global) == 1){
			mais_novo_global = mais_novo_local;
		}
	}
	return mais_novo_global;
}

Aluno procura_velho_na_turma(Turma T[], int qtd_turmas, int j){
	Aluno mais_velho = T[j].alunos[0];
	for(int i = 0; i < T[j].qtd; i++){
		if(primeiro_mais_velho(T[j].alunos[i], mais_velho) != 1){
			mais_velho = T[j].alunos[i];
		}
	}
	return mais_velho;
}

Aluno procura_velho_todas_turmas(Turma T[], int qtd_turmas){
	Aluno mais_velho_local;
	Aluno mais_velho_global = T[0].alunos[0];

	for(int i = 0; i < qtd_turmas; i++){
		mais_velho_local = procura_velho_na_turma(T, qtd_turmas, i);
		if(primeiro_mais_velho(mais_velho_local, mais_velho_global) != 1){
			mais_velho_global = mais_velho_local;
		}
	}
	return mais_velho_global;
}

int conta_substrings(Turma T[], int qtd_turmas, char *padrao){
	int total = 0;
	for(int i = 0; i < qtd_turmas; i++){
		for(int j = 0; j < T[i].qtd; j++){
			char *nome = T[i].alunos[j].nome;;
			char *obj = padrao;
			if(contem(nome, obj))total++;
		}
	}
	return total;
}

int add_aluno(Turma T[], Aluno A, int j){
	int ultima_pos = T[j].qtd;
	T[j].qtd = ultima_pos+1;
	
	if(*T[j].alunos[ultima_pos].nome == '\0'){
		for(int i = 0; i < sizeof(A.nome)-1; i++) T[j].alunos[ultima_pos].nome[i] = A.nome[i];
		for(int i = 0; i < sizeof(A.sobrenome)-1; i++){
			T[j].alunos[ultima_pos].sobrenome[i] = A.sobrenome[i];
		}
		T[j].alunos[ultima_pos].nascimento.ano = A.nascimento.ano;
		T[j].alunos[ultima_pos].nascimento.mes = A.nascimento.mes;
		T[j].alunos[ultima_pos].nascimento.dia = A.nascimento.dia;	
	}

	return T[j].qtd;
}

int remove_aluno(Turma T[], int j){
	int ultima_pos = T[j].qtd;
	T[j].qtd = ultima_pos - 1;
	if(*T[j].alunos[ultima_pos].nome == '\0'){
		*T[j].alunos[ultima_pos-1].nome = '\0';
	}
	return T[j].qtd;
}