# 📦 Bin Packing com GRASP + First Improvement (C++)

Este projeto implementa uma solução baseada em meta-heurística para o problema de *Bin Packing*, utilizando o método **GRASP (Greedy Randomized Adaptive Search Procedure)** combinado com uma **busca local do tipo First Improvement**.

---

## 🚀 Estratégia Utilizada

A solução é baseada em:

- **GRASP**:
  - Geração de solução inicial com uma abordagem gulosa e aleatória (RCL).
  - Refinamento com busca local.

- **First Improvement**:
  - Move um item para outro bin assim que encontra uma melhora na solução.
  - Aplica repetidamente até que nenhuma melhoria seja possível.

- **Importante**:
  - O algoritmo talvez não chegue na melhor solução, pois é algo aproximativo!
---

## 🛠️ Compilação

Compile com `g++`:

```bash
g++ main.cpp -o main
```

---

## 🧪 Execução

```bash
./main <tempo_em_segundos>
```

### 📥 Entrada (via stdin):

```
<capacidade_max_bin> <quantidade_itens> <RCL_size>
<tamanho_item_1>
<tamanho_item_2>
...
<tamanho_item_n>
```

---

### 📥 Entrada (via arquivo):

```bash
./bin_packing <tempo_em_segundos> < nomedoarquivo
```

O formato do arquivo deve respeitar as seguintes caracteristicas: 

```
<int: capacidade do bin> <int: quantidade_itens> <int: RCL_size>
<double: tamanho_item_1>
<double: tamanho_item_2>
...
<double: tamanho_item_n>
```

**Tem um exemplo no diretório input**

---

## 📤 Saída

- Mostra os bins usados com seus respectivos itens.
- Informa o total de bins na solução.
- Exibe a evolução da solução se forem encontradas melhorias.

---

## 📌 Parâmetros importantes

- `RCL_size`: Define o tamanho da lista de candidatos restrita usada na construção gulosa. Controla o nível de aleatoriedade.
- `tempo_em_segundos`: Quanto tempo o algoritmo irá executar o GRASP, buscando melhorar a solução.

---

## 📂 Estrutura do Código

- `item`: Estrutura que representa um item (id + tamanho).
- `bin`: Estrutura que representa um bin (capacidade + lista de itens).
- `greedy_randomized_construction`: Gera uma solução inicial usando uma estratégia gulosa com aleatoriedade.
- `first_improvement`: Aplica busca local movendo itens entre bins buscando a primeira melhora.
- `grasp`: Estrutura geral da meta-heurística.
- `print_bins`: Imprime a solução final.

---

## ✅ Validações Extras

- Verificação se o argumento de tempo é inteiro.
- Confirmação do número de itens lidos ao final.

---

## 📊 Resultados

- Utilizando o makefile no diretorio lista:

```bash
make 1q
```

---