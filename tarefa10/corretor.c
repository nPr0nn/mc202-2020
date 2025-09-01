#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TAD de uma tabela de Hash - Endereçamento Aberto
#define MAX 103
#define VAZIO "!!!!!!!!!\0"

typedef struct item{
	char chave[30];
}item;
typedef struct TabelaHash{
	item v[MAX];
	int quantidade;
}TabelaHash;
typedef TabelaHash *ponteiro_hash;

//Inicia o dicionario como Vazio
ponteiro_hash inicia_dicionario(ponteiro_hash dicionario){
	dicionario->quantidade = 0;
	for(int i = 0; i < MAX; i++){
		strcpy(dicionario->v[i].chave, VAZIO);
	}
	return dicionario;
}

// Funções de converter uma palavra para um numero inteiro
int hash1(char *palavra){
	int MOD = 103; 
	int p = 31;
	int valor_hash = 0;
	int potencia_p = 1;
	for(int i=0; i < strlen(palavra); i++){
		valor_hash = (valor_hash + (palavra[i] - 'a' + 1)*potencia_p) % MOD;
		potencia_p = (potencia_p*p) % MOD;
	}
	return valor_hash;
}
int hash2(char *palavra){
	int MOD = 101; 
	int p = 29;
	int valor_hash = 0;
	int potencia_p = 1;
	for(int i=0; i < strlen(palavra); i++){
		valor_hash = (valor_hash + (palavra[i] - 'a' + 1)*potencia_p) % MOD;
		potencia_p = (potencia_p*p) % MOD;
	}
	int indice = 97 - (valor_hash % 97);  
	return indice;
}

// Operações do dicionario
int pesquisa(ponteiro_hash dicionario, char *palavra){
	int indice_1 = hash1(palavra);
	int indice_2 = hash2(palavra);
	
	for(int i = 0; i < MAX; i++){
		int indice = (indice_1 + i*indice_2)%MAX;
		if(strcmp(dicionario->v[indice].chave, palavra) == 0){
			return 1;
		}
	}
	return 0;
}
ponteiro_hash inserir(ponteiro_hash dicionario, char *palavra){
	item celula;
	strcpy(celula.chave, palavra);
	int indice_1 = hash1(palavra);
	int indice_2 = hash2(palavra);

	for(int i = 0; i < MAX; i++){
		int indice = (indice_1 + i*indice_2)%MAX;
		if(strcmp(dicionario->v[indice].chave, VAZIO) == 0){
			dicionario->v[indice] = celula;
			break;
		}
	}

	return dicionario;
}

//Funções de manipulação de strings
void apagar_letra(char *palavra, int indice){
	if ((indice) <= strlen(palavra)){
		memmove(&palavra[indice],&palavra[indice+1],strlen(palavra)-indice);
		// strcpy(&palavra[indice-1],&palavra[indice]);
	}
}
char *substring(char *palavra, int indice, int tamanho){
   char *ponteiro;
   ponteiro = malloc(tamanho+1);
   int c;
   for(c = 0 ; c < tamanho ; c++ ) *(ponteiro+c) = *((palavra+indice-1)+c);   
   *(ponteiro+c) = '\0';   
   return ponteiro;
}
void inserir_letra(char *palavra, char c, int indice){
   char *antes_da_letra, *depois_da_letra;
   char *letra = malloc(2*sizeof(char));
   letra[0] = c;
   letra[1] = '\0';

   antes_da_letra = substring(palavra, 1, indice - 1 );      
   depois_da_letra = substring(palavra, indice, strlen(palavra)-indice+1);
   strcpy(palavra, "");
   strcat(palavra, antes_da_letra);
   strcat(palavra, letra);
   strcat(palavra, depois_da_letra);
   free(antes_da_letra);
   free(letra);
   free(depois_da_letra);
}

// Indentifica o tipo de erro
int correcao(ponteiro_hash dicionario, char *palavra){
	char alfabeto[26] = "abcdefghijklmnopqrstuvwxyz";
	char palavra_copia[30];
	strcpy(palavra_copia, palavra);
	if(pesquisa(dicionario, palavra) == 1) return 1;
	//verifica o tipo de erro
	else{
		for(int i = 0; i <= strlen(palavra); i++){
			apagar_letra(palavra, i);
			if(pesquisa(dicionario, palavra) == 1) return 2;
			strcpy(palavra, palavra_copia);
		}

		for(int i = 0; i <= strlen(palavra); i++){
			for(int j = 0; j < 26; j++){
				inserir_letra(palavra, alfabeto[j], (i+1));
				if(pesquisa(dicionario, palavra) == 1) return 2;
				strcpy(palavra, palavra_copia);
			}
		}

		for(int i = 0; i < strlen(palavra); i++){
			for(int j = 0; j < 26; j++){
				palavra[i] = alfabeto[j];
				if(pesquisa(dicionario, palavra) == 1) return 2;
			}
			palavra[i] = palavra_copia[i];
		}
	}
	return 3;
}

int main(){
	int numero_de_palavras_dicionario;
	int numero_de_palavras_texto;
	scanf("%d %d", &numero_de_palavras_dicionario, &numero_de_palavras_texto);
	scanf("%*c");

	// Inicio minha tabela Hash
	ponteiro_hash dicionario = malloc(sizeof(TabelaHash));
	dicionario = inicia_dicionario(dicionario);

	//Entrada do dicionario
	item palavra;
	for(int ii = 0; ii < numero_de_palavras_dicionario; ii++){
		scanf("%s", palavra.chave);
		scanf("%*c");
		dicionario = inserir(dicionario, palavra.chave);
	}

	//Processamento
	for(int i = 0; i < numero_de_palavras_texto; i++){
		scanf("%s", palavra.chave);
		scanf("%*c");
		int resultado = correcao(dicionario, palavra.chave);
		if(resultado == 1) printf("%s\n", "verde");
		else if(resultado == 2) printf("%s\n", "amarelo");
		else printf("%s\n", "vermelho");
	}

	free(dicionario);
}