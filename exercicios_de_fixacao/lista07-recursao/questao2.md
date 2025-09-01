Utilizando a biblioteca turtle, contida nos arquivos turtleC.h e turtle.c
obtidas da fonte: https://w3.cs.jmu.edu/lam2mo/cs240_2015_08/turtle.html foram feitos os programas:

(a) Estrela de Koch:

```c
#include "turtleC.h"

void koch(int tamanho, int nivel){
  int linha = tamanho/3;
  
  if(nivel == 1){
    turtle_forward(linha);
    turtle_turn_left(60);
    turtle_forward(linha);
    turtle_turn_right(120);
    turtle_forward(linha);
    turtle_turn_left(60);
    turtle_forward(linha);
  }
  
  else{
    koch(linha, nivel-1);
    turtle_turn_left(60);
    koch(linha, nivel-1);
    turtle_turn_right(120);
    koch(linha, nivel-1);
    turtle_turn_left(60);
    koch(linha, nivel-1);
  }
}

int main(){
    turtle_init(600, 600);

    int l, w;
    scanf("%d %d", &l, &w);
    koch(l, w);
    turtle_save_bmp("output.bmp"); 
    return EXIT_SUCCESS;
}
```

(b) Grade de triangulos:

```c
#include "turtleC.h"

void triangulo_aux1(int t){
  turtle_turn_left(60);
  turtle_forward(t);
  turtle_turn_left(120);
  turtle_forward(t);
  turtle_turn_left(120);
  turtle_forward(t);
  turtle_turn_left(60);
}

void triangulo_aux2(int n){
  int t = 100;
  turtle_forward(t);
  if(n > 1) triangulo_aux1(t);
  if(n == 1) return;
  triangulo_aux2(n-1);
}

void triangulo(int n){
  for(int i = 0; i < 3; i++){
    turtle_turn_left(120);
    triangulo_aux2(n);
  }
}

int main(){
    turtle_init(1000, 1000);
    triangulo(3);
    turtle_save_bmp("output.bmp"); 
    return EXIT_SUCCESS;
}
```
