#include <stdio.h>
#include <stdlib.h>

void printMat(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void cobrimento(int **matrix, int n) {
    int i, j;
    
    // Alocar memória para a matriz auxiliar
    int **mat = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        mat[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            mat[i][j] = matrix[i][j];
        }
    }

    int *linhaMarcada = (int *)calloc(n, sizeof(int));
    int *colunaMarcada = (int *)calloc(n, sizeof(int));
    int *qtdZerosLinha = (int *)calloc(n, sizeof(int));
    int *qtdZerosColuna = (int *)calloc(n, sizeof(int));
    
    // Contar zeros em cada linha e coluna
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] == 0) {
                qtdZerosLinha[i]++;
                qtdZerosColuna[j]++;
            }
        }
    }

    // Cobrir os zeros com o menor número de linhas e colunas
    while (1) {
        int maxLinha = -1, maxColuna = -1;
        int linhaMax = -1, colunaMax = -1;

        // Encontrar a linha ou coluna com mais zeros não cobertos
        for (i = 0; i < n; i++) {
            if (qtdZerosLinha[i] > maxLinha && !linhaMarcada[i]) {
                maxLinha = qtdZerosLinha[i];
                linhaMax = i;
            }
        }
        for (j = 0; j < n; j++) {
            if (qtdZerosColuna[j] > maxColuna && !colunaMarcada[j]) {
                maxColuna = qtdZerosColuna[j];
                colunaMax = j;
            }
        }

        // Se não há mais zeros a cobrir, sai do loop
        if (maxLinha == 0 && maxColuna == 0) break;

        // Priorizar cobrir a linha ou coluna com mais zeros
        if (maxLinha >= maxColuna) {
            linhaMarcada[linhaMax] = 1;
            for (j = 0; j < n; j++) {
                if (mat[linhaMax][j] == 0) {
                    qtdZerosColuna[j]--;
                }
            }
        } else {
            colunaMarcada[colunaMax] = 1;
            for (i = 0; i < n; i++) {
                if (mat[i][colunaMax] == 0) {
                    qtdZerosLinha[i]--;
                }
            }
        }
    }

    // Criar matriz final com as marcações
    for (i = 0; i < n; i++) {
        if (linhaMarcada[i]) {
            for (j = 0; j < n; j++) {
                mat[i][j] = -1;
            }
        }
    }
    for (j = 0; j < n; j++) {
        if (colunaMarcada[j]) {
            for (i = 0; i < n; i++) {
                mat[i][j] = -1;
            }
        }
    }

    // Exibir resultado do cobrimento
    printMat(mat, n);

    // Liberar memória alocada
    for (i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
    free(linhaMarcada);
    free(colunaMarcada);
    free(qtdZerosLinha);
    free(qtdZerosColuna);
}

int main() {
    int n = 4;
    int **matrix = (int **)malloc(n * sizeof(int *));
    int data[4][4] = {
        {7, 8, 0, 2}
        ,{40, 0, 18, 40},
         {0, 58, 0, 60},
          {0, 1, 96, 0}};
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = data[i][j];
        }
    }

    printf("Matriz original:\n");
    printMat(matrix, n);
    
    printf("\nMatriz apos o cobrimento:\n");
    cobrimento(matrix, n);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
