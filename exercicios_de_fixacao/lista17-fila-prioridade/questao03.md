Utilizar de uma estrutura de dados que se resuma em duas filas e prioridade, uma para realizar as
operações de retirar minimo e outra de máximo:

```c
typedef struct DuplaFila_de_Prioridade{
	p_fila_de_prioridade minima;
	p_fila_de_prioridade maxima;
}DuplaFila_de_Prioridade;
```

Em que o TAD de uma fila de prioridade seria:

```c
void troca(int *a, int *b){
  int t = *a;
  *a = *b;
  *b = t;
}
//TAD de uma Fila de Prioridade feita com Max-Heap
typedef struct FP{
  int *v;
  int n, tamanho;
}FP;
typedef FP * p_fila_de_prioridade;

p_fila_de_prioridade cria_fila_de_prioridade(int tamanho){
  p_fila_de_prioridade fila = malloc(sizeof(FP));
  fila->v = malloc(tamanho*sizeof(int));
  fila->n = 0;
  fila->tamanho = tamanho;
  return fila;
}

#define PAI(i) ((i-1)/2)
#define ESQ(i) (2*i+1)
#define DIR(i) (2*i+2)

void sobe_no_heap(p_fila_de_prioridade fila, int k){
  if(k > 0 && fila->v[PAI(k)] < fila->v[k]){
    troca(&fila->v[k], &fila->v[PAI(k)]);
    sobe_no_heap(fila, PAI(k));
  }
}

void desce_no_heap(p_fila_de_prioridade fila, int k){
  int maior_filho;
  if(ESQ(k) < fila->n){
    maior_filho = ESQ(k);
    if(DIR(k) < fila->n && fila->v[ESQ(k)] < fila->v[DIR(k)]){
      maior_filho = DIR(k);
    }
    if(fila->v[k] < fila->v[maior_filho]){
      troca(&fila->v[k], &fila->v[maior_filho]);
      desce_no_heap(fila, maior_filho);
    }
  }
}

void inserir_fila(p_fila_de_prioridade fila, int x){
  fila->v[fila->n] = x;
  fila->n++;
  sobe_no_heap(fila, fila->n-1);
}

int extrair(p_fila_de_prioridade fila){
  int x = fila->v[0];
  troca(&fila->v[0],&fila->v[fila->n - 1]);
  fila->n--;
  desce_no_heap(fila, 0);
  return (x);
}
```

As funções de operação então seriam:

```c
void inserir(DuplaFila_de_Prioridade DP, int x){
	inserir_fila(DP.minima, -x);
	inserir_fila(DP.maxima, x);
}

void extrair_maximo(DuplaFila_de_Prioridade DP, int x){
	int res = extrair(DP.maxima);
	return res;
}

void extrair_minimo(DuplaFila_de_Prioridade DP, int x){
	int res = extrair(DP.minima);
	return res;
}
```