Esboço de remoção arvore B

```
void Remover(x, k):
	Se a chave k está no nó x e x é uma folha:
		exclua a chave k de x.
	Se a chave k está no nó x e x é um nó interno:
		Se o filho y que precede k no nó x tem pelo menos t chaves:
			encontre o predecessor k' de k na subarvore com raiz y, delete recursivamente k' e substitua k por k' em x
		
		Se o filho z após k no nó x tem pelo menos t chaves:
			encontre o sucessor k' de k na subarvore com raiz z, delete recursivamente k' e substitua k por k' em x.
		
		Caso contrario Se  y e z ambos possuem apenas t-1 chaves:
			faça a junção de k e todas as chaves de z em y de forma que x perde tanto a chave k como o ponteiro para z, e y.
			libere z e delete recursivamente k de y
	Se a chave k não esta presente no nó interno x:
		determine a raiz ci[x] da subarvore apropriada que deve conter k e repita os passos.
```
