#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Lista Ligada - Definição
typedef struct No{
    int dado;
    struct No *prox;
}No;
typedef No * algarismo; 

// Lista Ligada - Operações Fundamentais
algarismo NovoNo(int dado){
    algarismo no = (algarismo) malloc(sizeof(struct No));
    no->dado = dado;
    no->prox = NULL;
    return no;
}
algarismo adiciona(algarismo numero, int dado){
    algarismo novo = NovoNo(dado);
    novo->prox = numero;
    return novo;
}
void destruir(algarismo No){
    if(No != NULL){
        destruir(No->prox);
        free(No);
    }
}
void imprimir(algarismo cabeca){
    algarismo ponteiro = cabeca;
    while(ponteiro){
        printf("%c", ponteiro->dado + '0');
        ponteiro = ponteiro->prox;
    }
    printf("\n");
}
int pega_tamanho(algarismo cabeca){
    int tamanho = 0;
    algarismo ponteiro = cabeca;
    while(ponteiro){
        tamanho++;
        ponteiro = ponteiro->prox;
    }
    return tamanho;
}

algarismo inverter(algarismo numero){
    algarismo atual, anterior, invertida = NULL;
    atual = numero;
    while (atual != NULL){
        anterior = atual;
        atual = anterior->prox;
        anterior->prox = invertida;
        invertida = anterior;
    }
    return invertida;
}

algarismo Copia(algarismo lista) {
    algarismo novo;
    if (lista == NULL) return NULL;
    novo = malloc(sizeof(No));
    novo->dado = lista->dado;
    novo->prox = Copia(lista->prox);
    return novo;
}

// Lista Ligada - Operações Auxiliares para Aritimetica 
int comparar(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2){
    //  1 | Primeiro é maior
    //  0 | São iguais
    // -1 | Segundo é maior
    if(tamanho1 > tamanho2) return 1;
    else if(tamanho1 < tamanho2) return -1;
    else{
        while(numero1 && numero2){
            if(numero1->dado != numero2->dado){
                if(numero1->dado > numero2->dado) return 1;
                else return -1;
                break;
            }
            numero1 = numero1->prox;
            numero2 = numero2->prox;
        }
    }
    return 0;
}
// Lista Ligada - Preenche a lista de algarismos do menor numero com zeros
algarismo cria_lista_de_zeros(int tamanho){  
    algarismo cabeca = NULL;  
    while (tamanho--)
        cabeca = adiciona(cabeca, 0); 
    return cabeca;  
} 
algarismo conserta_os_zeros(algarismo No, int diferenca) { 
    while(diferenca--){
        No = adiciona(No, 0);
    }
    return No;
} 

// Lista Ligada - Soma
void soma(algarismo numero1, algarismo numero2, algarismo *cabeca){
    algarismo NoAnterior = NULL;
    int carregar = 0;
    while (numero1 || numero2){
        int soma= 0;
        if (numero1) soma += numero1->dado;
        if (numero2) soma += numero2->dado;
        soma += carregar;
        carregar = soma / 10;
        soma = soma % 10;
        
        algarismo No = NULL;
        No = adiciona(No, soma);

        if (*cabeca == NULL){
            NoAnterior = No;
            *cabeca = No;
        }
        else{
            NoAnterior->prox = No;
            NoAnterior = No;
        }
        if (numero1) numero1 = numero1->prox;
        if (numero2) numero2 = numero2->prox;
    }
    if (carregar != 0){
        NoAnterior->prox = adiciona(NoAnterior->prox, carregar);
    }
}
algarismo somar(algarismo numero1, algarismo numero2){
    if(numero1 == NULL && numero2 == NULL) return NULL;
    algarismo resposta = NULL;
    algarismo numero1_copia = Copia(numero1);
    algarismo numero2_copia = Copia(numero2);

    numero1_copia = inverter(numero1_copia);
    numero2_copia = inverter(numero2_copia);

    soma(numero1_copia, numero2_copia, &resposta);

    destruir(numero1_copia);
    destruir(numero2_copia);
    resposta = inverter(resposta);
    return resposta;
}


// Lista Ligada - Subtração
algarismo subtrai_parte_02(algarismo numero1, algarismo numero2, int *emprestado){
    if(numero1 == NULL && numero2 == NULL && *emprestado == 0) return NULL;
    algarismo NoAnterior = subtrai_parte_02(numero1 ? numero1->prox : NULL, numero2 ? numero2->prox : NULL, emprestado); 
    int digito1 = numero1->dado; 
    int digito2 = numero2->dado; 
    int sub = 0;
    if(*emprestado){ 
        digito1--; 
        *emprestado = 0; 
    }   
    if (digito1 < digito2) { 
        *emprestado = 1;
        digito1 += 10;
    }   
    sub = digito1 - digito2; 
    algarismo atual = NovoNo(sub);  
    atual->prox = NoAnterior; 
    return atual; 
}
algarismo subtrai_parte_01(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2){
    if(numero1 == NULL && numero2 == NULL) return NULL;
    algarismo No1, No2 = NULL;
    algarismo No3;
    algarismo temporario1 = numero1;
    algarismo temporario2 = numero2;
    int diferenca = abs(tamanho1 - tamanho2);

    int iguais = 1;
    int zeros_foram_adicionados = 0;
    if (tamanho1 != tamanho2){ 
        No1 = tamanho1 > tamanho2 ? numero1 : numero2; 
        No2 = tamanho1 > tamanho2 ? numero2 : numero1; 
        No3 = Copia(No2);
        No3 = conserta_os_zeros(No3, diferenca);
        zeros_foram_adicionados = 1;
    } 
    else { 
        while (numero1 && numero2) { 
            if (numero1->dado != numero2->dado) { 
                No1 = numero1->dado > numero2->dado ? temporario1 : temporario2; 
                No2 = numero1->dado > numero2->dado ? temporario2 : temporario1;
                iguais = 0; 
                break; 
            } 
            numero1 = numero1->prox; 
            numero2 = numero2->prox; 
        }
        if(iguais == 1) return NovoNo(0);
    } 

    int emprestado = 0;
    algarismo resposta;
    if(zeros_foram_adicionados == 0) resposta = subtrai_parte_02(No1, No2, &emprestado);
    else resposta = subtrai_parte_02(No1, No3, &emprestado);

    while (resposta->dado == 0 && resposta->prox != NULL) {  
        algarismo auxiliar = resposta;  
        resposta = resposta->prox;  
        free(auxiliar);  
    }

    if(zeros_foram_adicionados == 1) destruir(No3);
    return resposta;
}
algarismo subtrair(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2){
    if(numero1 == NULL && numero2 == NULL) return NULL;
    algarismo resposta = NULL;
    algarismo numero1_copia = Copia(numero1);
    algarismo numero2_copia = Copia(numero2);

    resposta = subtrai_parte_01(numero1_copia, tamanho1, numero2_copia, tamanho2);
    destruir(numero1_copia);
    destruir(numero2_copia);
    return resposta;
}

// Lista Ligada - Multiplicação 
algarismo multiplica(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2)  {  
    algarismo resposta = cria_lista_de_zeros(tamanho1 + tamanho2 + 1);
    algarismo temporario1, resposta_p2;
    algarismo temporario2 = numero2;
    algarismo resposta_p1 = resposta;
    while(temporario2) {    
        int carregar = 0;  
        resposta_p2 = resposta_p1;    
        temporario1 = numero1;  
        while (temporario1) {  
            int mul = (temporario1->dado)*(temporario2->dado) + carregar;
            resposta_p2->dado += mul % 10;  
            carregar = mul/10 + (resposta_p2->dado)/10;  
            resposta_p2->dado = (resposta_p2->dado)%10; 
            temporario1 = temporario1->prox;  
            resposta_p2 = resposta_p2->prox;  
        }  
        if (carregar > 0) {  
            resposta_p2->dado += carregar;  
        }  
        resposta_p1 = resposta_p1->prox;  
        temporario2 = temporario2->prox;  
    }  
    resposta = inverter(resposta);  
    while (resposta->dado == 0 && resposta->prox != NULL) {  
        algarismo auxiliar = resposta;  
        resposta = resposta->prox;  
        free(auxiliar);  
    } 
    return resposta;  
}
algarismo multiplicar(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2) {
    if(numero1 == NULL && numero2 == NULL) return NULL;
    algarismo resposta = NULL;
    algarismo numero1_copia = Copia(numero1);
    algarismo numero2_copia = Copia(numero2);

    numero1_copia = inverter(numero1_copia);
    numero2_copia = inverter(numero2_copia);

    resposta = multiplica(numero1_copia, tamanho1, numero2_copia, tamanho2);

    destruir(numero1_copia);
    destruir(numero2_copia);
    return resposta;
}

algarismo divide_por_dois(algarismo numero, int tamanho) { 
    algarismo meio = NULL;
    int carregar = 0;
    while(numero != NULL){
        int temporario = numero->dado + carregar*10;
        meio = adiciona(meio, temporario/2);
        carregar = temporario%2;
        numero = numero->prox;
    }
    meio = inverter(meio);
    return meio; 
} 
algarismo divide(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2){
    algarismo resposta;
    if(tamanho1 == 1 && numero1->dado == 0) return NovoNo(0);
    int comparacao = comparar(numero1, tamanho1, numero2, tamanho2);
    if(comparacao != 1){
        resposta = comparacao == -1 ? NovoNo(0) : NovoNo(1);
        return resposta;
    }

    //Busca Binaria
    algarismo um = NovoNo(1);
    algarismo inicio = NovoNo(0);
    algarismo final = numero1;

    while(comparar(inicio, pega_tamanho(inicio), final, pega_tamanho(final)) < 0){
        algarismo diferenca = subtrair(inicio, pega_tamanho(inicio), final, pega_tamanho(final));
        diferenca = divide_por_dois(diferenca, pega_tamanho(diferenca));
        algarismo meio = somar(inicio, diferenca);
        
        algarismo produto = multiplicar(meio, pega_tamanho(meio), numero2, tamanho2);

        int comparacao2 = comparar(produto, pega_tamanho(produto), numero1, tamanho1);
        algarismo final_2 = Copia(final);
        algarismo inicio_2 = somar(inicio, um); 
        
        if(comparacao2 == 0){
            resposta = meio;
            break;
        }
        else if(comparacao2 == 1) final = subtrair(meio, pega_tamanho(meio), um, 1);
        else if(comparacao2 == -1) inicio = meio;

        resposta = final;
        if(comparar(inicio_2, pega_tamanho(inicio_2), final, pega_tamanho(final)) == 0){
            algarismo produto2 = multiplicar(inicio_2,pega_tamanho(inicio_2),numero2, tamanho2);
            int comparacao3 = comparar(produto2, pega_tamanho(produto2), numero1, tamanho1);
            if(comparacao2 == -1){
                destruir(produto2);
                if(comparacao3 == 1) resposta = inicio;
                else resposta = final_2;
                break;
            }
            destruir(produto2);
        }
        destruir(diferenca);
        destruir(produto);
        destruir(final_2);
        destruir(inicio_2);
    }

    algarismo produto3 = multiplicar(resposta,pega_tamanho(resposta), numero2, tamanho2);
    if(comparar(produto3, pega_tamanho(produto3), numero1, tamanho1) == 1){
        resposta = subtrair(resposta,pega_tamanho(resposta),um, 1);
    }
    while (resposta->dado == 0 && resposta->prox != NULL) {  
        algarismo auxiliar = resposta;  
        resposta = resposta->prox;  
        free(auxiliar);  
    }
    destruir(um);
    destruir(produto3);
    return resposta;
}

algarismo dividir(algarismo numero1, int tamanho1, algarismo numero2, int tamanho2){
    if(numero1 == NULL && numero2 == NULL) return NULL;
    algarismo resposta = NULL;
    algarismo numero1_copia = Copia(numero1);
    algarismo numero2_copia = Copia(numero2);
    
    resposta = divide(numero1_copia, tamanho1, numero2_copia, tamanho2);
    
    destruir(numero1_copia);
    destruir(numero2_copia);
    return resposta; 
}

int main() { 
    int numero_de_operacoes;
    scanf("%d", &numero_de_operacoes);
    char c;
    for(int i = 0; i < numero_de_operacoes; i++){
        algarismo resposta = NULL; 
        algarismo numero1 = NULL; 
        algarismo numero2 = NULL;
        char numeroA[100], numeroB[100];
        scanf(" %c", &c);
        scanf(" %s %s", numeroA, numeroB);

        int tamanho1 = strlen(numeroA);
        int tamanho2 = strlen(numeroB);

        for(int i = strlen(numeroA)-1; i>=0; i--) numero1 = adiciona(numero1, (numeroA[i] - '0'));
        for(int i = strlen(numeroB)-1; i>=0; i--) numero2 = adiciona(numero2, (numeroB[i] - '0'));

        if(c == '+') resposta = somar(numero1, numero2);
        else if(c == '-') resposta = subtrair(numero1, tamanho1, numero2, tamanho2);
        else if(c == '*') resposta = multiplicar(numero1, tamanho1, numero2, tamanho2);
        else if(c == '/') resposta = dividir(numero1, tamanho1, numero2, tamanho2);

        imprimir(resposta);
        destruir(resposta);
        destruir(numero1);
        destruir(numero2);
    }
}  