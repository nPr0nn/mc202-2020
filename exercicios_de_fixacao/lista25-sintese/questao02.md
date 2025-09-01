
(a) Assim como árvores binárias generalizam a ideia de listas encadeadas, árvores binárias de busca generalizam a ideia de listas encadeadas crescentes, são muito utilizadas para se representar uma grande conjunto de dados onde se deseja encontrar um elemento de acordo com a sua chave. Em uma árvore de busca é possível encontrar-se qualquer chave existente descendo-se a árvore, sempre à esquerda toda vez que a chave procurada for menor do que a chave do nodo visitado e sempre à direita toda vez que for maior. A escolha da direção de busca só depende da chave que se procura e da chave que o nodo atual possui. A busca de um elemento em uma árvore balanceada com n elementos toma tempo médio < log(n), tendo a busca então O(log n). Graças à estrutura de árvore a busca poderá ser feita com apenas log(n) comparações de elementos.

Arvore AVL: A árvore AVL é uma árvore de busca binária perfeitamente balanceada, em que a diferença entre as alturas das subárvores esquerda e direita não pode ser mais de um para todos os nós.

Arvore vermelho-preto: Uma árvore vermelho-preto é um tipo de árvore de busca binária perfeitamente balanceadas, onde cada nó tem um bit extra, e esse bit é frequentemente interpretado como a cor (vermelho ou preto). Essas cores são usadas para garantir que a árvore permaneça equilibrada durante as inserções e remoções.

Arvore de afunilamento: Como AVL e Red-Black Trees, a árvore de afunilamento também é uma arvore binaria de busca perfeitamente balanceada.A ideia principal da árvore de afunilamento é trazer o item acessado recentemente para a raiz da árvore, isso torna o item pesquisado recentemente acessível no tempo O (1) se acessado novamente


(b) Concordo, a implementação de uma arvore B em um caso que muitas atualizações não tenham que ser feitas
 nelas e seja mais realizado operações de busca seria mais vantajoso em termos de complexidade e organização de 
 dados do que a implementação de uma arvore binaria, visto que possui uma altura menor.
