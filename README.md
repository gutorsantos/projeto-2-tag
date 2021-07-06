# Projeto
Este projeto consiste na implementação do Algoritmo de Gale-Shapley para o encontrar o emparelhamento máximo estável entre uma lista de professores e escolas.

Haviam duas possibilidades de escolha de linguagem, C e C++. A escolhida foi **Linguagem C**.

## Algoritmo de Gale-Shapley

Na ciência da computação, o algoritmo de Gale-Shapley é um algoritmo para encontrar uma solução para o problema de emparelhamento estável, nomeado em homenagem a David Gale e Lloyd Shapley, que o descreveram como uma solução tanto para o problema de admissão na faculdade quanto para o problema do casamento estável. Leva tempo polinomial, e o tempo é linear no tamanho da entrada para o algoritmo. Dependendo de como é usado, ele pode encontrar a solução ideal para os participantes de um lado da correspondência ou para os participantes do outro lado. É um mecanismo confiável do ponto de vista dos participantes para os quais fornece a solução ideal. [(Wikipédia)](https://en.wikipedia.org/wiki/Gale%E2%80%93Shapley_algorithm)


## Execução

Basta compilar o arquivo principal main.c que terá como saída um executável exe (Windows) ou out (Unixes)
```
gcc main.c -o main.out
```
E executá-lo
```
// (Windows)
a

// (Unixes / Mac OS X)
chmod a+x a.out
./a.out
```

## Resultados

Ao final da execução, foram alocados **66 professores**.
