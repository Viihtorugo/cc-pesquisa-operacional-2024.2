# Otimização de Sensores em Cidades Inteligentes: Tráfego Urbano

Este repositório apresenta um projeto de pesquisa operacional voltado à otimização do posicionamento de sensores em centros urbanos, utilizando dados reais da cidade de Maceió e modelagem por Programação Linear Inteira (ILP) com o solver CPLEX.

## Objetivo

Desenvolver modelos matemáticos para resolver o problema de cobertura de vértices a distância-N, a fim de posicionar sensores de trânsito de forma eficiente, minimizando o número de sensores instalados e maximizando a cobertura de monitoramento.

## Estrutura de Pastas

```
artigo/
├── src/                    # Códigos-fonte C++ e Python
    ├── input/              # Arquivos de entrada em .txt
    ├── output/             # Arquivos de saída em .txt
    ├── create_data.ipynb   # Arquivo .ipynb com extração dos dados e visualização das saídas
    ├── classic.cpp         # Arquivo .cpp com ILP cobertura de vértices mínima, saída out1.txt
    ├── main.cpp            # Arquivo .cpp com ILP cobertura de vértices distância N, saída outN.txt
    
├── README.md
```

## Estrutura do Projeto


### 1. Coleta de Dados

* Realizada em Python com a biblioteca `osmnx` para extrair o grafo de ruas do centro de Maceió.
* Identificação de vértices com semáforos a partir de atributos do OpenStreetMap.
* Arquivos gerados no formato `.txt` com os seguintes dados:

  * Distância de cobertura do sensor (d)
  * Lista de vértices e arestas
  * Vértices com grau e com semáforos

### 2. Modelagem Matemática

* Implementação em C++ utilizando o CPLEX.
* Duas abordagens:

  * Cobertura de Vértices Mínima (sem distância)
  * Cobertura de Vértices a Distância-N (com restrição de alcance dos sensores)


## 3. Requisitos

* Python 3.x com pacotes: `osmnx`, `matplotlib`, `numpy`
* C++ com suporte ao CPLEX instalado
* Compilador LaTeX (ex: pdflatex) para compilar o artigo

### 4. Execução

* O código resolve instâncias para diferentes valores de distância (30m, 100m, 250m, 500m, 1000m).
* Visualização dos grafos com resultados utilizando `matplotlib`.

## Como Usar

1. Execute os scripts do create_data.ipynb para gerar os arquivos de entrada.
2. Compile os modelos em C++ com CPLEX para resolver as instâncias. 
    1. Para abordagem clássica, execute no terminal: `make classic`
    2. Para abordagem da distância n, execute no terminal: `make run` (verificar qual input está na linha 35 e já output está na linha 156)
3. Visualize os resultados com os arquivos de saída ou no arquivo create_data.ipynb execute a partir do bloco Abordagem Clássica - Cobertura de Vertices.

## Referências

* OpenStreetMap & osmnx: [https://github.com/gboeing/osmnx](https://github.com/gboeing/osmnx)
* IBM CPLEX Optimization Studio
* Bazaraa, Jarvis, Sherali - "Programas Lineares e Otimização Combinatória"

## Autores

* Victor Hugo S. A. ([vhsa@ic.ufal.br](mailto:vhsa@ic.ufal.br))
* Hugo Coêlho S. ([hcs@ic.ufal.br](mailto:hcs@ic.ufal.br))
