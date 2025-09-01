// TAD de um array (lista) de strings
typedef struct Lista_de_Strings{
	char **lista_de_strings;
	int tamanho;
}Lista_de_Strings;
typedef Lista_de_Strings *p_lista_de_strings;

p_lista_de_strings criar_lista_de_strings(){
	p_lista_de_strings lista = malloc(sizeof(Lista_de_Strings));
	lista->lista_de_strings = malloc(sizeof(char*));
	lista->tamanho = 0;
	return lista;
}

// Inserir uma string e alocar a memoria na lista de strings
void inserir_na_lista_de_strings(p_lista_de_strings lista, char *string){
	lista->lista_de_strings = realloc(lista->lista_de_strings, (lista->tamanho+1)*(MAX*sizeof(char)));
	lista->lista_de_strings[lista->tamanho] = malloc(MAX*sizeof(char));
	strcpy(lista->lista_de_strings[lista->tamanho], string);
	lista->tamanho++;
}

void destruir_lista_de_strings(p_lista_de_strings lista){
	for(int i = 0; i < lista->tamanho; i++){
		free(lista->lista_de_strings[i]);
	}
}

// Pegar substring do indice "inicio" até o indice "fim"
char* substring(char *original, int inicio, int fim){
    int tamanho = fim - inicio;
    char *substr = malloc((tamanho+2)*sizeof(char));
    memcpy(substr, &original[inicio], tamanho+1);
    char quebra[1];
	quebra[0] = '\0';
    strcat(substr, quebra);
    return substr;
}

// Transforma uma string em uma lista de strings
void dividir_string(char *string, p_lista_de_strings lista){
	char *token;
	lista->tamanho = 0;  	
	while( (token = __strtok_r(string, " ", &string)) ){
		inserir_na_lista_de_strings(lista, token);
	}
}

// Verifica se um dado caracter representa um digito 0-9
int eh_digito(char caracter){
	if ((caracter>='0') && (caracter<='9')) return 1;
    return 0;
}

// Funções para passar uma expressao em string Infixa para Posfixa
// Ordem de precedencia de operações
int precedencia(char caracter){ 
    switch (caracter){ 
    	case '+': 
    	case '-': 
        	return 1;
        //Se necessario adicionar outras operações aqui
    } 
    return -1; 
}
void Infixa_para_Posfixa(p_lista_de_strings lista, p_lista_de_strings pos_lista){
	char string_auxiliar[3];
	pos_lista->tamanho = 0;
	pilha stack = criar_pilha(lista->tamanho);

	for(int i = 0; i<lista->tamanho; i++){
		if(strlen(lista->lista_de_strings[i]) > 1){
			inserir_na_lista_de_strings(pos_lista, lista->lista_de_strings[i]);
		}
		else if(strlen(lista->lista_de_strings[i]) == 1){
			if(lista->lista_de_strings[i][0] == '('){
				push(stack, lista->lista_de_strings[i][0]);
			}
			else if(lista->lista_de_strings[i][0] == ')'){
				while(!pilha_vazia(stack) && ver_pilha_topo(stack) != '('){
					string_auxiliar[0] = pop(stack);
					string_auxiliar[1] = '\0';
					inserir_na_lista_de_strings(pos_lista, string_auxiliar);
				}
				if(!pilha_vazia(stack) && ver_pilha_topo(stack) != '(') return;
				else pop(stack);
			}
			else{
				while(!pilha_vazia(stack) &&
					   precedencia(lista->lista_de_strings[i][0]) <= precedencia(ver_pilha_topo(stack))){
					string_auxiliar[0] = pop(stack);
					string_auxiliar[1] = '\0';
					inserir_na_lista_de_strings(pos_lista, string_auxiliar);
				}
				push(stack, lista->lista_de_strings[i][0]);
			}
		}
	}

	while(!pilha_vazia(stack)){
		string_auxiliar[0] = pop(stack);
		string_auxiliar[1] = '\0';
		inserir_na_lista_de_strings(pos_lista, string_auxiliar);
	}

	free(stack->v);
	free(stack);
	return;
}