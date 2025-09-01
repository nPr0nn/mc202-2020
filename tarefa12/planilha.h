#define ERRO 0x3f3f3f3f

// TAD para uma Planilha de dados
typedef struct Celula{
	char *celula;
	int visitada; 
	int tipo; // 0 - numero || 1 - expressao
}Celula;
typedef Celula** Planilha;

// Funções de criação da Planilha
Planilha criar_planilha(int colunas, int linhas){
	Planilha planilha = malloc(colunas*linhas*sizeof(Celula));
	for(int i = 0; i < linhas; i++){
		planilha[i] = malloc(colunas*sizeof(Celula));
	}
	return planilha;
}
void destruir_planilha(Planilha planilha, int colunas, int linhas){
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			free(planilha[i][j].celula);
		}
		free(*(planilha + i));
	}	
}
void Preencher_planilha_com_CSV(FILE *ponteiro_para_arquivo, Planilha planilha){
	char *item = malloc(MAX*sizeof(char));
	int char_temporario ;
	int tamanho_do_item = 1, ind_col = 0, ind_lin = 0;

	int expressao = 0;
	strcpy(item, "");
	while( (char_temporario = fgetc(ponteiro_para_arquivo)) ){
		if(char_temporario == EOF) break;
		if(char_temporario == ',' || char_temporario == '\n'){
			planilha[ind_lin][ind_col].celula = malloc(MAX*sizeof(char));
			char quebra[1];
			quebra[0] = '\0';
			strcat(item, quebra);
			strcpy(planilha[ind_lin][ind_col].celula, item);
			planilha[ind_lin][ind_col].tipo = 0;
			planilha[ind_lin][ind_col].visitada = 0;
			if(expressao == 1){
				planilha[ind_lin][ind_col].tipo = 1;
				expressao = 0;
			}
			ind_col++;
			if(char_temporario == '\n'){
				ind_lin++;
				ind_col = 0;
			}
			tamanho_do_item = 1;
			expressao = 0;
			strcpy(item, "");
		}
		else if(char_temporario == '=') expressao = 1;
		else if(char_temporario != ' ' && char_temporario != '='){
			tamanho_do_item++;
			char char_adicionado[2]; 
			char_adicionado[0] = char_temporario;
			char_adicionado[1] = '\0';
			if(expressao && strlen(item) >= 1 && !(eh_digito(char_temporario)) ) strcat(item, " ");
			strcat(item, char_adicionado);
		}
	}
	free(item);
}
void imprimir_planilha(Planilha planilha, int colunas, int linhas){
	for(int i = 0; i < linhas; i++){
		for(int j = 0; j < colunas; j++){
			char ci = 65 + j; 
			printf("%s %c%c%d%c ", planilha[i][j].celula, '[', ci, (i+1),']');
		}
		printf("\n");
	}
}

// Funções auxiliares para Planilha
int valor_da_expressao(Planilha planilha, char *coordenada, int pi, int pj, int **processados){
	int erro = 0;
	if(processados[pi][pj] != ERRO) return processados[pi][pj];

	//Caso Numerico
	if(planilha[pi][pj].tipo != 1){
		planilha[pi][pj].visitada = 0;
		return processados[pi][pj] = atoi(planilha[pi][pj].celula); //caso chegue em um valor numerico
	}
	
	// Caso Expressao simples
	char *string = malloc(MAX*sizeof(char));
	strcpy(string, planilha[pi][pj].celula);
	p_lista_de_strings lista = criar_lista_de_strings();
	p_lista_de_strings pos_lista = criar_lista_de_strings();
	dividir_string(string, lista);

	if(lista->tamanho == 1){
		char *num_linha = substring(coordenada, 1, strlen(coordenada));
		int i = (atoi(num_linha)) - 1 ;
		int j = (coordenada[0] - 'A');
		free(num_linha);

		if(planilha[i][j].visitada == 1){
			free(string);
			destruir_lista_de_strings(lista);
			free(lista->lista_de_strings);
			free(lista);
			destruir_lista_de_strings(pos_lista);
			free(pos_lista->lista_de_strings);
			free(pos_lista);
			return ERRO;
		}

		planilha[pi][pj].visitada = 1;
		int valor = valor_da_expressao(planilha, lista->lista_de_strings[0], i, j, processados);
		planilha[pi][pj].visitada = 0;

		free(string);
		destruir_lista_de_strings(lista);
		free(lista->lista_de_strings);
		free(lista);
		destruir_lista_de_strings(pos_lista);
		free(pos_lista->lista_de_strings);
		free(pos_lista);
		return processados[i][j] = valor;
	}

	// Caso Expressao Composta
	Infixa_para_Posfixa(lista, pos_lista);
	pilha stack = criar_pilha(pos_lista->tamanho);
	char *num_linha = malloc(MAX*sizeof(char));
	int valor_total = 0;

	for(int k = 0; k < pos_lista->tamanho; k++){
		if(strlen(pos_lista->lista_de_strings[k]) > 1){
			free(num_linha);
			num_linha = substring(pos_lista->lista_de_strings[k], 1, strlen(pos_lista->lista_de_strings[k]));
			int i = (atoi(num_linha)) - 1 ;
			int j = (pos_lista->lista_de_strings[k][0] - 'A');
			planilha[pi][pj].visitada = 1;

			if( ( (i == pi && j == pj) || (planilha[i][j].visitada == 1) ) ){ erro = 1; break; }
			int valor = valor_da_expressao(planilha, pos_lista->lista_de_strings[k], i, j, processados);
			if(valor == ERRO){ erro = 1; break; }
			
			planilha[pi][pj].visitada = 0;
			push_int(stack, valor);
		}
		else{
			int valor1 = pop_int(stack);
			int valor2 = pop_int(stack);
			switch(pos_lista->lista_de_strings[k][0]){
				case '+': push_int(stack, valor1 + valor2); break;
				case '-': push_int(stack, valor2 - valor1); break;
			}
		}
	}
	valor_total = pop_int(stack);

	free(num_linha);
	free(string);
	destruir_lista_de_strings(lista);
	free(lista->lista_de_strings);
	free(lista);
	destruir_lista_de_strings(pos_lista);
	free(pos_lista->lista_de_strings);
	free(pos_lista);
	free(stack->v);
	free(stack);
	if(erro == 1) return ERRO;
	return processados[pi][pj] = valor_total;
}

//Funções das Operações Principais na Planilha
void leitura(Planilha planilha, char *coordenada, int colunas, int linhas){
	char *num_linha = substring(coordenada, 1, strlen(coordenada));
	int i = (atoi(num_linha)) - 1 ;
	int j = (coordenada[0] - 'A');
	free(num_linha);
	int valor;

	// Manter controle de celulas processadas em uma recursao para evitar re-calculo
	int **processados = malloc((linhas+1)*(colunas+1)*sizeof(int));
	for(int h = 0; h <= linhas; h++){
		processados[h] = malloc((colunas+1)*sizeof(int));
		for(int k = 0; k <= colunas; k++) processados[h][k] = ERRO;
	}

	// Caso seja uma expressão
	if(planilha[i][j].tipo == 1){
		valor = valor_da_expressao(planilha, planilha[i][j].celula, i, j, processados);
	}
	else{
		valor = atoi(planilha[i][j].celula);
	}

	// Liberar memoria
	for(int h = 0; h <= linhas; h++) free(processados[h]);
	free(processados);

	if(valor == ERRO) printf("%s%c %s\n", coordenada,':',"#ERRO#");
	else printf("%s%c %d\n", coordenada,':',valor);
	return;
}
void escrita(Planilha planilha, char *coordenada, char *novo_valor){
	char *num_linha = substring(coordenada, 1, strlen(coordenada));
	int i = (atoi(num_linha)) - 1 ;
	free(num_linha);
	int j = (coordenada[0] - 'A');
	char *valor_antigo = malloc(sizeof(planilha[i][j].celula));

	strcpy(valor_antigo, planilha[i][j].celula);
	strcpy(planilha[i][j].celula, novo_valor);
	printf("%s%c %s %s %s\n", coordenada,':',valor_antigo, "->" ,planilha[i][j].celula);
	free(valor_antigo);
	return;
}