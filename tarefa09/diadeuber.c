#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//TAD do cliente de Uber
typedef struct cliente{
	char nome[1000];
	double avaliacao;
	int xc, yc;
	int xd, yd;
}cliente;

//Troca a posição na memoria de dois numeros
void troca(cliente *a, cliente *b){
	cliente t = *a;
	*a = *b;
	*b = t;
}
//TAD de uma Fila de Prioridade feita com Max-Heap
typedef struct FP{
	cliente *v;
	int n, tamanho;
}FP;
typedef FP * p_fila_de_prioridade;

p_fila_de_prioridade cria_fila_de_prioridade(int tam){
	p_fila_de_prioridade fila = malloc(sizeof(FP));
	fila->v = malloc(tam*sizeof(cliente));
	fila->n = 0;
	fila->tamanho = tam;
	return fila;
}

#define PAI(i) ((i-1)/2)
#define ESQ(i) (2*i+1)
#define DIR(i) (2*i+2)

void sobe_no_heap(p_fila_de_prioridade fila, int k){
	if(k > 0 && fila->v[PAI(k)].avaliacao < fila->v[k].avaliacao){
		troca(&fila->v[k], &fila->v[PAI(k)]);
		sobe_no_heap(fila, PAI(k));
	}
}

void desce_no_heap(p_fila_de_prioridade fila, int k){
	int maior_filho;
	if(ESQ(k) < fila->n){
		maior_filho = ESQ(k);
		if(DIR(k) < fila->n && fila->v[ESQ(k)].avaliacao < fila->v[DIR(k)].avaliacao){
			maior_filho = DIR(k);
		}
		if(fila->v[k].avaliacao < fila->v[maior_filho].avaliacao){
			troca(&fila->v[k], &fila->v[maior_filho]);
			desce_no_heap(fila, maior_filho);
		}
	}
}

void insere(p_fila_de_prioridade fila, cliente x){
	fila->v[fila->n] = x;
	fila->n++;
	sobe_no_heap(fila, fila->n-1);
}

cliente extrai_maximo(p_fila_de_prioridade fila){
	cliente x = fila->v[0];
	troca(&fila->v[0],&fila->v[fila->n - 1]);
	fila->n--;
	desce_no_heap(fila, 0);
	return x;
}

cliente pega_maximo(p_fila_de_prioridade fila){
	return fila->v[0];
}

void retira(p_fila_de_prioridade fila, int i){
	fila->v[i] = pega_maximo(fila);
	sobe_no_heap(fila, i);
	extrai_maximo(fila);
}

int pega_indice(p_fila_de_prioridade fila, char **nome){
	for(int i = 0; i < fila->n; i++){
		if(strcmp(fila->v[i].nome, *nome) == 0) return i;
	}
	return -1;
}

//Função principal
int main(){
	p_fila_de_prioridade uber = cria_fila_de_prioridade(500);
	char acao;
	double preferencia_max = 5000;

	int xm = 0;
	int ym = 0;

	int km = 0;
	int km_efetivo = 0;
	double rendimento_bruto = 0;
	double despesas = 0;
	double rendimento_liquido = 0;

	//Processa entradas
	while(1){
		cliente passageiro;
		scanf("%c", &acao);
		if(acao == 'T') {
			break;
		}
		if(acao == 'A'){
			scanf("%s", passageiro.nome);
			double valor;
			scanf("%lf", &valor);
			if(uber->n == 0) passageiro.avaliacao = valor + preferencia_max;
			else passageiro.avaliacao = valor;
			scanf("%d%d%d%d", &passageiro.xc, &passageiro.yc, &passageiro.xd, &passageiro.yd);
			insere(uber, passageiro);
			printf("%s %s %s\n","Cliente", passageiro.nome, "foi adicionado(a)");
		}
		if(acao == 'F'){
			cliente entregue = extrai_maximo(uber);
			km += abs(entregue.xc - xm) + abs(entregue.yc - ym);
			km += abs(entregue.xd - entregue.xc) + abs(entregue.yd - entregue.yc);
			km_efetivo += abs(entregue.xd - entregue.xc) + abs(entregue.yd - entregue.yc);
			xm = entregue.xd;
			ym = entregue.yd;
			if(uber->n >= 1) uber->v[0].avaliacao += preferencia_max;
			printf("%s %s %s\n", "A corrida de", entregue.nome, "foi finalizada");
		}
		if(acao == 'C'){
			char *nome_cancelado = malloc(100*sizeof(char));
			rendimento_bruto += 7;
			scanf("%s", nome_cancelado);
			int indice = pega_indice(uber, &nome_cancelado);
			retira(uber, indice);
			printf("%s %s\n", nome_cancelado, "cancelou a corrida");		
			free(nome_cancelado);
			if(uber->n == 1) uber->v[0].avaliacao += preferencia_max;
		}
		scanf("%*c");
	}
	printf("\n");

	//Retorna as informações das corridas do dia
	double aluguel = 57;
	double custo_da_gasolina = (((double)km)/10)*(4.104);
	despesas = custo_da_gasolina+aluguel;

	rendimento_bruto += ((double)km_efetivo)*1.4;
	rendimento_liquido = rendimento_bruto - despesas - rendimento_bruto/4;

	printf("%s\n","Jornada finalizada. Aqui esta o seu rendimento de hoje");
	printf("%s %d\n","Km total:", km);
	printf("%s %.2lf\n","Rendimento bruto:", rendimento_bruto);
	printf("%s %.2lf\n","Despesas:", despesas);
	printf("%s %.2lf\n","Rendimento liquido:", rendimento_liquido);

	free(uber->v);
	free(uber);
}