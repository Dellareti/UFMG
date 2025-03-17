# Trabalho Prático 2 - Avaliação do Evento

## Descrição
Este trabalho prático foi desenvolvido para a disciplina de Algoritmos 1 da Universidade Federal de Minas Gerais (UFMG). O objetivo foi solucionar o problema computacional conhecido como "Avaliação do Evento" utilizando algoritmos de divisão e conquista.

## Problema
O problema envolve um grupo de amigos que assistem a shows sequenciais no festival Rock In Rio. Eles usam um aplicativo para avaliar cada show com notas de -5 a 5. O objetivo é determinar qual intervalo de shows consecutivos mais agradou ao grupo, somando todas as avaliações, para que possam planejar seu retorno ao próximo festival.

Como os shows acontecem em sequência e os amigos não podem sair e voltar ao festival, eles precisam determinar o melhor intervalo contíguo de shows para assistir.

## Modelagem
O problema foi modelado utilizando o paradigma de divisão e conquista, especificamente implementando o algoritmo de subarranjo máximo (Maximum Subarray). Este algoritmo possui as seguintes etapas:

1. Dividir o array em duas partes
2. Retornar o máximo entre:
   - Soma máxima do subarray na metade esquerda (recursivamente)
   - Soma máxima do subarray na metade direita (recursivamente)
   - Soma máxima do subarray que atravessa o ponto médio

## Estrutura do Projeto
- `main.cpp`: Ponto de entrada do programa
- `rock.cpp`: Implementação da estrutura e algoritmos
- `rock.hpp`: Declaração das estruturas e funções
- `Makefile`: Configuração para compilação do projeto

## Estruturas de Dados
- Arrays para armazenar as avaliações dos shows
- Struct `resultado` para armazenar os índices de início e fim do subarray, além do valor da soma

## Algoritmos Implementados
- `max_crossing_sum()`: Encontra a soma máxima possível no arranjo que atravessa o ponto médio (complexidade O(n))
- `max_sub_array_sum()`: Retorna a soma do subarray de soma máxima (complexidade O(n log n))
- `escolhe_melhores_shows()`: Utiliza as funções anteriores para determinar o melhor intervalo de shows consecutivos

## Compilação e Execução
Para compilar o programa:
```
make
```

Para executar o programa com um arquivo de entrada:
```
./tp02 < arquivo_de_entrada.txt
```

Para salvar a saída em um arquivo:
```
./tp02 < arquivo_de_entrada.txt > arquivo_de_saida.txt
```

Para limpar os arquivos de compilação:
```
make clean
```

## Formato de Entrada
- Primeira linha: Dois inteiros A e S (número de amigos e número de shows)
- Próximas A linhas: S números reais separados por espaço (avaliações de cada amigo para cada show)
- A entrada termina quando A = S = 0

## Formato de Saída
- Para cada caso de teste, o programa imprime uma linha contendo dois números inteiros Xi e Xf
- Xi é o índice do primeiro show que eles devem assistir
- Xf é o índice do último show que eles devem assistir
- O intervalo [Xi, Xf] é inclusivo nas duas pontas

## Autor
Ítalo Dell'Areti - Universidade Federal de Minas Gerais (UFMG)

## Ambiente de Desenvolvimento
O programa foi desenvolvido e testado em um ambiente Linux distribuição Ubuntu 22.04 LTS utilizando Visual Studio Code e compilado com G++ da GNU Compiler Collection.

## Links da Implementação
- Vídeo da implementação:
  - Dropbox: https://www.dropbox.com/s/ag92gyau05ictc9/TP2%20ALG.mp4?dl=0
  - Google Drive: https://drive.google.com/file/d/1NQ6ZWSxsFZ9A0bdlSWH88sPtbKXcP0Tm/view?usp=sharing

## Bibliografia
- Geeks for geeks: Maximum Subarray Sum using Divide and Conquer algorithm
- Geeks for geeks: Divide and Conquer
- Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein. Algoritmos: Teoria e Prática. 3a edição.
