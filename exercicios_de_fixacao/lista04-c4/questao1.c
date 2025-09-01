#include <stdio.h>

#include <stdio.h>
#include <string.h>

typedef struct{
	double real;
	double imaginaria;
}complexo;

complexo inicializar(){
	complexo a;
	scanf("%lf", &a.real);
	scanf("%lf", &a.imaginaria);
	return a;
}

void imprimir(complexo a){
	printf("%lf %c %c%lf", a.real, '+', 'i', a.imaginaria);
}

complexo operacao(complexo a, complexo b, char operador){
	complexo res;
	if(operador == '+'){
		res.real = a.real + b.real;
		res.imaginaria = a.imaginaria + b.imaginaria;
	}
	else if(operador == '-'){
		res.real = a.real - b.real;
		res.imaginaria = a.imaginaria - b.imaginaria;
	}
	else if(operador == '*'){
		res.real = a.real*b.real - a.imaginaria*b.imaginaria;
		res.imaginaria = a.real*b.imaginaria + a.imaginaria*b.real;
	}
	else if(operador == '/'){
		double baixo = b.real*b.real + b.imaginaria*b.imaginaria;
		res.real = (a.real*b.real + a.imaginaria*b.imaginaria)/baixo;
		res.imaginaria = (a.imaginaria*b.real - a.real*b.imaginaria)/baixo;
	}
	return res;
}

complexo potencia_inteira(complexo a, int p){
	complexo res = a;
	while(p > 1){
		res = operacao(res, a, '*'); 
		p--;
	}
	return res;
}

int comparar(complexo a, complexo b){
	if(a.real == b.real && a.imaginaria == b.imaginaria) return 1;
	return 0;
}

complexo conjugado(complexo a){
	complexo res;
	res.real = a.real;
	res.imaginaria = -a.imaginaria;
	return res;
}

int main(){
	complexo a;
	complexo b;
	a = inicializar();
	// b = operacao(a, a, '*');
	b = potencia_inteira(a, 2);
	imprimir(b);
}