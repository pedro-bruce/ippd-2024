# Relatório Final: Distância de Levenshtein

---

## Introdução

O problema desenvolvido neste trabalho foi retirado da **13th Marathon of Parallel Programming – WSCAD 2018**.  

A Distância de Levenshtein, nomeada em homenagem ao matemático soviético Vladimir Levenshtein, é uma métrica que mede a diferença entre duas strings. Essa diferença é o número mínimo de edições de caracteres necessários para transformar uma string em outra. As edições possíveis são:

- **Inserção** de um caractere;
- **Remoção** de um caractere;
- **Substituição** de um caractere.

### Definição Matemática

A distância de Levenshtein entre duas strings \(a\) e \(b\) (com comprimentos respectivos \(|a|\) e \(|b|\)) é dada por \(lev_{a,b}(|a|, |b|)\), definida como:

\[
lev_{a,b}(i, j) =
\begin{cases} 
\max(i, j) & \text{se } \min(i, j) = 0, \\
\min \begin{cases}
lev_{a,b}(i-1, j) + 1, \\
lev_{a,b}(i, j-1) + 1, \\
lev_{a,b}(i-1, j-1) + 1_{(a_i \neq b_j)}
\end{cases} & \text{caso contrário}.
\end{cases}
\]

Aqui, \(1_{(a_i \neq b_j)} = 0\) se \(a_i = b_j\) e \(1\) caso contrário. Assim, \(lev_{a,b}(i, j)\) representa a distância entre os primeiros \(i\) caracteres de \(a\) e os primeiros \(j\) caracteres de \(b\).

### Exemplo

A distância de Levenshtein entre **"chicken"** e **"kicking"** é **4**, pois as edições necessárias são:

1. **Remover** a primeira letra: `chicken → hicken`;
2. **Substituir** a primeira letra: `hicken → kicken`;
3. **Substituir** a penúltima letra: `kicken → kickin`;
4. **Inserir** a última letra: `kickin → kicking`.

---

## Objetivos

O objetivo deste trabalho é avaliar o impacto da programação paralela, utilizando **OpenMP**, na resolução do problema de cálculo da Distância de Levenshtein. 

O ponto de partida foi um código sequencial retirado do site [GeeksforGeeks](https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/), implementado originalmente em **C++**, que foi adaptado para **C** neste projeto.

---

## Avaliação Experimental

### Strings Utilizadas

Para os experimentos, utilizamos as seguintes strings:

- **String 1**: `"abcdeabcdeabcde"` (15 caracteres)
- **String 2**: `"zzzzzzzzzzz"` (11 caracteres)

Essas strings foram escolhidas para demonstrar a eficiência do algoritmo de cálculo da **Distância de Levenshtein** em um cenário com diferenças significativas.

### Resultados

A tabela abaixo apresenta os resultados obtidos ao calcular a distância de Levenshtein entre as duas strings utilizando diferentes números de threads com OpenMP. O tempo de execução é medido em segundos.

| **Número de Threads** | **Distância de Levenshtein** | **Tempo (s)** |
|------------------------|-----------------------------|---------------|
| 1                      | 10                          | 0.293919      |
| 2                      | 10                          | 0.162817      |
| 4                      | 10                          | 0.125280      |
| 8                      | 10                          | 0.083515      |
| 16                     | 10                          | 0.052704      |
| 32                     | 10                          | 0.050645      |

**Observação:** A distância de Levenshtein calculada foi **10**, indicando que são necessárias 10 operações para transformar a **String 1** na **String 2**. O tempo de execução reduz com o aumento do número de threads, mostrando a eficácia da paralelização com OpenMP.

### Otimização com o Uso de Condicional no Paralelismo

Durante a implementação paralela do algoritmo de cálculo da Distância de Levenshtein, foi observado que o uso de uma condição no pragma `#pragma omp task` é fundamental para o desempenho eficiente. A condicional `if (m > 5 && n > 5)` garante que tarefas paralelas sejam criadas apenas para subproblemas suficientemente grandes, enquanto os menores são resolvidos sequencialmente. Isso evita a sobrecarga associada à criação de tarefas para subproblemas pequenos, onde o custo de paralelizar supera os benefícios. Sem essa condicional, o número de tarefas criadas aumenta exponencialmente. Isso pode ser observado inclusive quando executamos o código paralelo com apenas uma thread, obtendo o valor reportado na tabela acima, e ao executar o código sequencial, que não há esse controle da recursão, aumentando em mais de 10 vezes o tempo de execução.


---
