//TAD de uma pilha (stack)
typedef struct Pilha{ 
    unsigned tamanho; 
    int topo; 
    int* v; 
}Pilha; 
typedef struct Pilha * pilha;

// Operações na pilha 
pilha criar_pilha(unsigned tamanho){ 
    pilha stack = (pilha) malloc(sizeof(Pilha)); 
    if(!stack) return NULL; 
    stack->topo = -1; 
    stack->tamanho = tamanho;
    stack->v = (int*) malloc(stack->tamanho*sizeof(int)); 
    return stack; 
} 
int pilha_vazia(pilha stack){ 
    return stack->topo == -1 ; 
} 

// Operações em uma stack de caracteres
char ver_pilha_topo(pilha stack){ 
    return stack->v[stack->topo]; 
} 
char pop(pilha stack){ 
    if (!pilha_vazia(stack)) return stack->v[stack->topo--]; 
    return '$'; 
} 
void push(pilha stack, char elemento){ 
    stack->v[++stack->topo] = elemento; 
}

// Operações em uma stack de Inteiros
int ver_pilha_topo_int(pilha stack){ 
    return stack->v[stack->topo]; 
} 
int pop_int(pilha stack){ 
    if (!pilha_vazia(stack)) return stack->v[stack->topo--]; 
    return '$'; 
} 
void push_int(pilha stack, int elemento){ 
    stack->v[++stack->topo] = elemento; 
}