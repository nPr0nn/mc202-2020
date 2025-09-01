
	Em ambos os caso é vantajoso montar uma struct para representar um ponto em R2, possuindo ela
como elementos dois inteiros para as coordenadas (x e y), dependendo das operações esse ponto podem
ser organizados em outras estruturas de dados, no caso dado pela questão essas estruturas poderiam ser:

(a) Uma fila de prioridade criada com max-heap baseada no valor de x, para assim buscar o par (x, y)
com maior valor de x em O(logN) 

(b) Uma fila de prioridade criada com max-heap baseada na distancia dos ponto a origem, para assim retirar o ponto (x, y) mais distante em O(logN) 