Utilizando o TAD de fila de prioridade em um arquivo "prioridade.h" com o seguinte codigo:

```c
//Troca a posição na memoria de dois numeros
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

void inserir(p_fila_de_prioridade fila, int x){
  x = -x;
  fila->v[fila->n] = x;
  fila->n++;
  sobe_no_heap(fila, fila->n-1);
}

int extrair_minimo(p_fila_de_prioridade fila){
  int x = fila->v[0];
  troca(&fila->v[0],&fila->v[fila->n - 1]);
  fila->n--;
  desce_no_heap(fila, 0);
  return (x);
}

```

Basta inserir todos os valores das k listas na fila de prioridade e retirar o minimo m vezes, colocando-o em um vetor.
