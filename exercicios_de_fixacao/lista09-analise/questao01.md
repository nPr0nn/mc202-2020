(a)
     -- $O(n^5)$
     -- $O(nlog(n)$
     -- $O(2^n)$
     -- $O(2^{log(n)}$
     -- $O(n^n)$

(b)  Dadas funções assintoticamente não-negativas $f$ e $g$, dizemos que $f$ está na ordem $O$ de $g$ e escrevemos  $f = Ο(g)$  se existe um número positivo $c$ tal que  $f(n) \leq c \cdot g(n)$  para todo $n$ suficientemente grande. Em outras palavras, se existem números positivos $c$ e $n_{0}$ tais que $f(n) \leq c \cdot g(n)$ para todo $n$ maior que $n_{0}$ 

-- Supondo a expressão $2^n = O(2^{n - 0,001})$ temos que existem $c$ e $n_0$ tais que $2^n \leq c \cdot 2^{n - 0,001}$ para todo $n \geq n_0$ o que implica que $n  \leq (log_2(c) - 0,001) + n$, o que é coerente, portanto a suposição é verdade.

   -- Supondo a expressão $2^n = O(2^{n (1- 0,001)})$ temos que existem $c$ e $n_0$ tais que $2^n \leq c \cdot 2^{n(1 - 0,001)}$ para todo $n \geq n_0$  o que implica que  $n \leq log_2(c) + 0,999n \rightarrow n \leq 1000 \cdot log_2(c)$, um absurdo, portanto a suposição está incorreta.
     
   -- Supondo a expressão $n^2 = O(n^{1,999})$ temos que existem $c$ e $n_0$ tais que $n^2 \leq c \cdot n^{1,999}$ para todo $n \geq n_0$ o que implica que $n^{1/1000} \leq c \rightarrow n \leq c^{1000}$, um absurdo, portanto a suposição está incorreta.
  
