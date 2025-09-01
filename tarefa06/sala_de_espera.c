#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TAD de um Paciente
typedef struct Paciente{
	char nome[50];
	char prioridade[15];
	int chamadas[1000];

	int quantidade_de_consultas;
	int consulta_atual;
	int minutos_gastos;
	int emFila;
	int indentidade;
}Paciente;

// Deque - Fila - Estrutura
typedef struct No{
	Paciente dado;
	struct No *prox;
	struct No *ante;		
}No;
typedef No *no_ponteiro;

typedef struct deque{
	no_ponteiro frente;
	no_ponteiro costas;
	int tamanho;
}deque;

no_ponteiro NovoNo(Paciente dado){
	no_ponteiro no = (no_ponteiro) malloc(sizeof(No));
	no->dado = dado;
	no->prox = NULL;
	no->ante = NULL;
	return no;
}

void destruir_no(no_ponteiro no){
	if(no != NULL){
		destruir_no(no->prox);
		free(no);
	}
}

deque criar_deque(){
	deque dq;
	dq.frente = NULL;
	dq.costas = NULL;
	dq.tamanho = 0;
	return dq; 
}

// Deque - Fila - Funções
void imprimir_deque(deque dq, int i){
	printf(" %s%d%s", "Fila ", i, ": ");
	while(dq.frente != NULL){
		printf("%s | ", dq.frente->dado.nome);
		dq.frente = dq.frente->prox;
	}
	printf("\n");
}

void apaga_deque(deque dq){
	dq.costas = NULL;
	while(dq.frente != NULL){
		no_ponteiro temporario = dq.frente;
		dq.frente->ante = NULL;
		dq.frente = dq.frente->prox;
		free(temporario);
	}
	dq.tamanho = 0;
}

deque inserirFrente(deque dq, Paciente x){
	no_ponteiro no = NovoNo(x);
	if(dq.frente == NULL) dq.frente = dq.costas = no;
	else{
		no->prox = dq.frente;
		dq.frente->ante = no;
		dq.frente = no;
	}
	dq.tamanho++;
	return dq;
}

deque inserirCostas(deque dq, Paciente x){
	no_ponteiro no = NovoNo(x);
	if(dq.frente == NULL) dq.frente = dq.costas = no;
	else{
		no->ante = dq.costas;
		dq.costas->prox = no;
		dq.costas = no;
	}
	dq.tamanho++;
	return dq;
}

deque removeFrente(deque dq){
	no_ponteiro temporario = dq.frente;
	if(dq.frente == NULL) return dq;
	if(dq.frente == dq.costas) dq.frente = dq.costas = NULL;
	else{
		dq.frente = dq.frente->prox;
		dq.frente->ante = NULL;
	}
	free(temporario);
	dq.tamanho--;
	return dq;
}


void vazio(deque dq){
	if(dq.frente == NULL) printf("%s\n", "vazio");
	else printf("%s\n", "nao vazio");
}


// Minimo entre dois inteiros a e b
int min(int a, int b){
	if(a < b) return a;
	return b;
}


// Conversão de tempo
void minutos_para_horario(int tempo_minutos, char **horario_de_saida){
	char horas_string[5];
	char minutos_string[5];
	char minutos_string_real[5];

	strcpy(minutos_string_real, ":");
	strcpy(horas_string, "");
	strcpy(minutos_string, "");

	int horas = 8 + (tempo_minutos/60);
	int minutos = tempo_minutos%60;

	sprintf(horas_string, "%d", horas);
	sprintf(minutos_string, "%d", minutos);

	if(strlen(horas_string) < 2){
		strcat(horas_string, "0");
		horas_string[1] = horas_string[0];
		horas_string[0] = '0';
	}
	if(strlen(minutos_string) < 2) strcat(minutos_string, "0");

	strcat(minutos_string_real, minutos_string);
	strcat(horas_string, minutos_string_real);

	strcpy(*horario_de_saida, horas_string);
}

// Função principal
int main(){
	int indice = 0;
	int total_pacientes = 0;
	Paciente *pacientes = malloc(1000*sizeof(Paciente));
	deque filas[10];
	int numero_de_profissionais[10] = {0, 10, 2, 5, 3, 4, 7, 2, 1, 4};

	//Criar todas as filas de profissionais
	for(int i = 1; i <= 9; i++) filas[i] = criar_deque();

	//Entrada
	while(1){
		int j = 0;
		char numeros[10000];

		if(scanf("%*c") == EOF) break;
		scanf("%[^\"]", pacientes[indice].nome);
		scanf("%*c");
		scanf("%*c");
		scanf("%[A-Za-z ]", pacientes[indice].prioridade);
		scanf("%[^\n]", numeros);
		scanf("%*c");

		pacientes[indice].quantidade_de_consultas = 0;

		for(int i = 0; i < strlen(numeros); i++){
			if(numeros[i] != ' '){
				pacientes[indice].quantidade_de_consultas++;
				pacientes[indice].chamadas[j] = numeros[i] - '0';
				j++;
			}
		}

		pacientes[indice].consulta_atual = 0;
		pacientes[indice].minutos_gastos = 0;
		pacientes[indice].emFila = 0;
		pacientes[indice].indentidade = indice;
		indice++;
	}
	total_pacientes = indice;

	//Processamento de dados
	int tempo_minutos = 0;
	while(1){
		int termino_das_consultas = 1;
		tempo_minutos += 10;
		
		indice = 0;
		while(indice < total_pacientes){
			if(pacientes[indice].consulta_atual != pacientes[indice].quantidade_de_consultas){
				termino_das_consultas = 0;
				int fila_chamada_indice = pacientes[indice].consulta_atual;
				int fila_tipo = pacientes[indice].chamadas[fila_chamada_indice];

				if(pacientes[indice].emFila == 0){
					pacientes[indice].consulta_atual++;
					if(strcmp(pacientes[indice].prioridade, "normal ") == 0) {
						filas[fila_tipo] = inserirCostas(filas[fila_tipo], pacientes[indice]);
					}
					else{
						filas[fila_tipo] = inserirFrente(filas[fila_tipo], pacientes[indice]);
					}
					pacientes[indice].emFila = 1;
				}
			}
			indice++;
		}

		for(int i = 1; i <=9; i++){
			int numero_de_atendimentos;
			numero_de_atendimentos = min(numero_de_profissionais[i], filas[i].tamanho); 
			while(numero_de_atendimentos--){
				//Quando um paciente tiver todas suas consultas feitas liberar ele no horario de saida
				if(filas[i].frente->dado.consulta_atual == filas[i].frente->dado.quantidade_de_consultas){
					char *horario_de_saida = malloc(10*sizeof(char));
					minutos_para_horario(tempo_minutos, &horario_de_saida);
					printf("%s ", horario_de_saida);
					printf("%s", filas[i].frente->dado.nome);
					printf("\n");
					free(horario_de_saida);
				}
				pacientes[filas[i].frente->dado.indentidade].emFila = 0;
				filas[i] = removeFrente(filas[i]);
			}
		}
		if(termino_das_consultas)break;
	}
	free(pacientes);
	for(int i = 1; i<=9; i++) apaga_deque(filas[i]);
}