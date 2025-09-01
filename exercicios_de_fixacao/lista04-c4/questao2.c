#include <stdio.h>
#include <stdbool.h>

#define eps 10e-9
typedef struct 
{
	double x;
	double y;
}ponto;

typedef struct {
	ponto pts[100000];
	int tam;
}poligono;

double max(double a, double b){
	if(a - b > eps) return a;
	return b;
}
double min(double a, double b){
	if(a - b < eps) return a;
	return b;
}

poligono iniciar_poligono(int n){
	poligono poli;
	ponto p;
	for(int i = 0; i < n; i++){
		scanf("%lf", &p.x);
		scanf("%lf", &p.y);
		poli.pts[i] = p;
	}
	poli.tam = n;
	return poli;
}

bool colineares(ponto p1, ponto p2, ponto p3){ 
    bool c1 = (p3.x <= max(p1.x, p2.x)) && (p3.x >= min(p1.x, p2.x));
    bool c2  = (p3.y <= max(p1.y, p2.y)) && (p3.y >= min(p1.y, p2.y));
    return (c1 && c2);
}

int orientacao(ponto p1, ponto p2, ponto p3){
	double res = (p2.x - p1.x)*(p3.y - p2.y) - (p3.x - p2.x)*(p2.y - p1.y);
	if(res > 0) return 1;
	else if(res < 0) return -1;
	return 0;
} 

double area(poligono poli){
	double area = 0;
	for(int i = 0; i < poli.tam; i++){
		ponto p1 = poli.pts[i];
		ponto p2 = poli.pts[(i+1)%poli.tam];
		area += (p2.x + p1.x)*(p2.y - p1.y);
	}
	return area/2;
}

poligono transladar(poligono poli, double xt, double yt){
	poligono res;
	for(int i = 0; i < poli.tam; i++){
		res.pts[i].x = poli.pts[i].x + xt;
		res.pts[i].y = poli.pts[i].y + yt;
	}
	res.tam = poli.tam;
	return res;
}

int main(){

}