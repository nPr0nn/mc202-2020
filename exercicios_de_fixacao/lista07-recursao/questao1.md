
-- Versão Recursiva
```c
int potencia_recursiva(int x, int n){
	if(n == 1) return x;
	return x*potencia_recursiva(x, n-1); 
}
```

-- Versão Iterativa
```c
int potencia_iterativa(int x, int n){
	int tmp = x;
	for(int i = 0; i < n-1; i++) x *= tmp;
	return x;
}
```

-- A versão recursiva do fatorial vai realizar mais iterações por conta de recalculos e 
operações com pilha, as duas podem ser feitas com O(1) de espaço.