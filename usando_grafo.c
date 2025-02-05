#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para imprimir uma matriz quadrada n x n
void printMat(int **matriz, int n) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
}

/*
 * Busca em profundidade para encontrar um emparelhamento para a linha i.
 * Apenas considera as arestas onde o elemento é 0.
 *
 * Parâmetros:
 *   i               - linha atual
 *   n               - dimensão da matriz (n x n)
 *   matriz          - matriz de custo (usamos os zeros para criar o grafo bipartido)
 *   visitado        - vetor para marcar as colunas já visitadas nesta chamada
 *   emparelhamento  - vetor de tamanho n, onde emparelhamento[j] é a linha emparelhada com a coluna j (-1 se nenhuma)
 *
 * Retorna true se foi possível emparelhar a linha i com alguma coluna.
 */
bool buscaEmparelhamento(int i, int n, int **matriz, bool *visitado, int *emparelhamento) {
    for (int j = 0; j < n; j++){
        if (matriz[i][j] == 0 && !visitado[j]) {
            visitado[j] = true;
            if (emparelhamento[j] == -1 || buscaEmparelhamento(emparelhamento[j], n, matriz, visitado, emparelhamento)) {
                emparelhamento[j] = i;
                return true;
            }
        }
    }
    return false;
}

/*
 * Busca de caminhos alternados (DFS) a partir da linha i.
 * Essa função marca as linhas e colunas “alcançadas” a partir de linhas não emparelhadas.
 *
 * Parâmetros:
 *   i                - linha atual
 *   n                - dimensão da matriz
 *   matriz           - matriz de custo (para identificar zeros)
 *   linhasVisitadas  - vetor booleano para marcar linhas alcançadas
 *   colunasVisitadas - vetor booleano para marcar colunas alcançadas
 *   emparelhamento   - vetor de emparelhamento (emparelhamento[j] = linha emparelhada com a coluna j)
 */
void buscaAlternada(int i, int n, int **matriz, bool *linhasVisitadas, bool *colunasVisitadas, int *emparelhamento) {
    for (int j = 0; j < n; j++){
        if (matriz[i][j] == 0 && !colunasVisitadas[j]) {
            colunasVisitadas[j] = true;
            if (emparelhamento[j] != -1 && !linhasVisitadas[emparelhamento[j]]) {
                linhasVisitadas[emparelhamento[j]] = true;
                buscaAlternada(emparelhamento[j], n, matriz, linhasVisitadas, colunasVisitadas, emparelhamento);
            }
        }
    }
}

/*
 * Função que realiza o cobrimento dos zeros.
 *
 * A ideia é:
 *   1. Encontrar o emparelhamento máximo no grafo bipartido formado pelas linhas e colunas
 *      onde há zero (isto é, criar um emparelhamento usando buscaEmparelhamento).
 *   2. A partir das linhas não emparelhadas, executar DFS para identificar os caminhos alternados.
 *   3. Segundo o procedimento padrão, a cobertura mínima é:
 *         - Todas as linhas NÃO alcançadas pela DFS (não visitadas)
 *         - Todas as colunas alcançadas pela DFS (visitadas)
 *   4. **Se a cobertura mínima for trivial (todas as linhas ou todas as colunas), a função não altera a matriz.**
 *   5. Caso contrário, para cada posição (i, j) cuja linha ou coluna esteja na cobertura, o valor é alterado para -1.
 */
void cobrimento(int **matrizOriginal, int n) {
    int i, j;
    
    // Cria uma cópia da matriz original para não alterá-la durante a busca.
    int **matriz = malloc(n * sizeof(int *));
    if (!matriz) {
        fprintf(stderr, "Erro ao alocar memória para a matriz auxiliar.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n; i++){
        matriz[i] = malloc(n * sizeof(int));
        if (!matriz[i]) {
            fprintf(stderr, "Erro ao alocar memória para a linha %d da matriz auxiliar.\n", i);
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < n; j++){
            matriz[i][j] = matrizOriginal[i][j];
        }
    }
    
    // Etapa 1: Encontra o emparelhamento máximo.
    // emparelhamento[j] será a linha emparelhada com a coluna j (-1 se não houver).
    int *emparelhamento = malloc(n * sizeof(int));
    if (!emparelhamento) {
        fprintf(stderr, "Erro ao alocar memória para emparelhamento.\n");
        exit(EXIT_FAILURE);
    }
    for (j = 0; j < n; j++)
        emparelhamento[j] = -1;
    
    // Para cada linha, tenta emparelhar com alguma coluna (usando DFS).
    for (i = 0; i < n; i++){
        bool *visitado = calloc(n, sizeof(bool));
        if (!visitado) {
            fprintf(stderr, "Erro ao alocar memória para visitado.\n");
            exit(EXIT_FAILURE);
        }
        buscaEmparelhamento(i, n, matriz, visitado, emparelhamento);
        free(visitado);
    }
    
    // Etapa 2: A partir das linhas NÃO emparelhadas, busca caminhos alternados.
    bool *linhasVisitadas = calloc(n, sizeof(bool));
    bool *colunasVisitadas = calloc(n, sizeof(bool));
    if (!linhasVisitadas || !colunasVisitadas) {
        fprintf(stderr, "Erro ao alocar memória para vetores de visitação.\n");
        exit(EXIT_FAILURE);
    }
    // Marque as linhas que não conseguiram emparelhamento.
    for (i = 0; i < n; i++){
        bool emparelhada = false;
        for (j = 0; j < n; j++){
            if (emparelhamento[j] == i) {
                emparelhada = true;
                break;
            }
        }
        if (!emparelhada) {
            linhasVisitadas[i] = true;
            buscaAlternada(i, n, matriz, linhasVisitadas, colunasVisitadas, emparelhamento);
        }
    }
    
    // Etapa 3: Determina a cobertura mínima.
    // Segundo o procedimento padrão:
    //   - Linhas NÃO visitadas (não alcançadas) fazem parte da cobertura.
    //   - Colunas visitadas fazem parte da cobertura.
    bool *linhasCobertas = malloc(n * sizeof(bool));
    bool *colunasCobertas = malloc(n * sizeof(bool));
    if (!linhasCobertas || !colunasCobertas) {
        fprintf(stderr, "Erro ao alocar memória para linhasCobertas ou colunasCobertas.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n; i++){
        linhasCobertas[i] = !linhasVisitadas[i];  // linhas não alcançadas → cobertas
    }
    for (j = 0; j < n; j++){
        colunasCobertas[j] = colunasVisitadas[j];   // colunas alcançadas → cobertas
    }
    
    // Conta quantas linhas e quantas colunas foram cobertas.
    int numLinhasCobertas = 0, numColunasCobertas = 0;
    for (i = 0; i < n; i++){
        if (linhasCobertas[i])
            numLinhasCobertas++;
    }
    for (j = 0; j < n; j++){
        if (colunasCobertas[j])
            numColunasCobertas++;
    }
    
    // Se a cobertura for trivial (ou seja, se todas as linhas OU todas as colunas forem cobertas),
    // então NÃO alteramos a matriz. Essa condição evita "cobrir" toda a matriz com -1.
    if (numLinhasCobertas == n || numColunasCobertas == n) {
        printf("\nCobertura mínima trivial encontrada (todas as linhas ou todas as colunas).\n");
        printf("A matriz não foi alterada:\n");
        printMat(matrizOriginal, n);
    } else {
        // Etapa 4: Atualiza a matriz auxiliar:
        // Para cada posição (i, j) cuja linha ou coluna esteja na cobertura, coloca -1.
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                if (linhasCobertas[i] || colunasCobertas[j])
                    matriz[i][j] = -1;
            }
        }
        printf("\nMatriz após o cobrimento (linhas/colunas cobertas marcadas com -1):\n");
        printMat(matriz, n);
    }
    
    // Libera a memória alocada
    for (i = 0; i < n; i++){
        free(matriz[i]);
    }
    free(matriz);
    free(emparelhamento);
    free(linhasVisitadas);
    free(colunasVisitadas);
    free(linhasCobertas);
    free(colunasCobertas);
}

/*
 * Função principal de teste.
 */
int main() {
    int n = 4, i, j;
    
    // Aloca a matriz original
    int **matriz = malloc(n * sizeof(int *));
    if (!matriz) {
        fprintf(stderr, "Erro ao alocar memória para a matriz original.\n");
        exit(EXIT_FAILURE);
    }
    
    // Dados de exemplo para a matriz
    int dados[4][4] = {
        { 0,  8,  1,  2},
        {40,  1, 0, 40},
        { 0, 58,  0, 60},
        { 0,  1, 96,  0}
    };
    
    // Copia os dados para a matriz alocada dinamicamente
    for (i = 0; i < n; i++){
        matriz[i] = malloc(n * sizeof(int));
        if (!matriz[i]) {
            fprintf(stderr, "Erro ao alocar memória para matriz[%d].\n", i);
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < n; j++){
            matriz[i][j] = dados[i][j];
        }
    }
    
    // Exibe a matriz original
    printf("Matriz original:\n");
    printMat(matriz, n);
    
    // Chama a função que realiza o cobrimento dos zeros
    cobrimento(matriz, n);
    
    // Libera a memória da matriz original
    for (i = 0; i < n; i++){
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}
