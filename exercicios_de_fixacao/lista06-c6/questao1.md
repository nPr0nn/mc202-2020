(a) O programa retorna um erro de "Segmentation fault" além de conter erros na função de trocar valores.
então não é possível determinar uma saída ou parte dela.

(b) Existe, a memoria alocada pela função "void g" não é liberada.

(c):

```
#include <stdio.h>
#include <stdlib.h>

void f(int *a, int *b){
	int c = *a;
	*a = *b;
	*b = c;
}

void g(int **c, int n){
	*c = malloc(sizeof(int)*n);
}

void h(int *h){
	*h = 100;
}

int main(){
	int a =1, b = 2, c= 3;
	int **d = malloc(2*sizeof(int*));	
	f(&a, &b);	
	g(&d[1], 2);
	h(&d[1][1]);
	printf("%d %d %d", a, c, d[1][1]);
	free(d[1]); 
	free(d);
	return 0;
}
```