#include <stdio.h>
#include <stdlib.h>



/*
    Cobrimento - fazer uma nova matriz 
    

    1 - Pegar a ultima matriz feita: Passar o menor numero de retas
    nas linhas ou/e colunas para cortar todos os zeros. casos:

    a) numeros não riscados
    b) numeros riscados 1 vez 
    c) numeros riscados 2 vezes

    passos: gerar uma nova tabela

    A) Escolher o menor numero do item a) e vai subtrai-lo de todos os não riscados
    e colocalos nos seus respectivos locais.

    B) repita os numeros do item b) no mesmo local que estão

    C) Soma cada item de c) ao menor numero do item a)

 */

void printMat(int matrix[4][4], int n) {
    printf("\n");
    for(int i = 0 ; i < n; i++) {
        for(int j = 0 ; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


int indice_dos_zeros(int matrix[4][4], int n) {
    int aux = 0;
    int lista_indice_i[4];
    int lista_indice_j[4];

    for (int i =0; i < n; i++) {
        lista_indice_i[i] = -1;
        lista_indice_j[i] = -1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = aux; j < n; j++) {
            if(matrix[i][j] == 0) {
                lista_indice_i[i] = i;
                lista_indice_j[i] = j;
                aux += 1;
                break;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%d", lista_indice_i[i]);
        printf("%d ", lista_indice_j[i]);
    }

    printf("\n");
    
    return 0;
}




void cobrimento(int matrix[4][4], int n) {
    int i, j;
    int mat[4][4];

    // Copiando a matriz original
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            mat[i][j] = matrix[i][j];
        }
    }

    int linhaMarcada[4] = {0};
    int colunaMarcada[4] = {0};
    
    // Contar zeros em cada linha e coluna
    int qtdZerosLinha[4] = {0};
    int qtdZerosColuna[4] = {0};
    
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
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
                mat[i][j] = -1; // Linha riscada
            }
        }
    }
    for (j = 0; j < n; j++) {
        if (colunaMarcada[j]) {
            for (i = 0; i < n; i++) {
                mat[i][j] = -1; // Coluna riscada
            }
        }
    }

    // Exibir resultado do cobrimento
    printMat(mat, n);
}


// {13,14,0,8}, 
// {40,0,12,40}, 
// {6,64,0,66}, 
// {0,1,90,0}}

// {0,2,4,3}, 
// {2,0,0,3}, 
// {0,6,8,2}, 
// {2,0,0,0}



int main( ) {

    int matriz[4][4] = {
        {13,14,0,8}, 
        {40,0,12,40}, 
        {6,64,0,66}, 
        {0,1,90,0}};

    printMat(matriz, 4);
    indice_dos_zeros(matriz, 4);

    cobrimento(matriz, 4);

    return 0;
}



