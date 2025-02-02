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




int cobrimento(int matrix[4][4], int n) {
    // Fazer uma cópia da matriz
    int i, j;
    int mat[4][4];

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            mat[i][j] = matrix[i][j];
        }
    }

    // Inicio da lógica de cobrimento
    int qtd_zeros_linha = 0;
    int *indice_zeros = NULL;
    int aux = 1;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(int k = 0; k < n ; k++) {
                if(matrix[i][j] == 0) {
                    qtd_zeros_linha += 1;
                    aux++;
                }
            break;
            }
        }
        indice_zeros = realloc(indice_zeros, aux * sizeof(int));
        indice_zeros[i] = qtd_zeros_linha;
        qtd_zeros_linha = 0;
    }

    // Inicio da lógica de cobrimento
    int qtd_zeros_coluna = 0;
    int *indice_zeros_coluna = NULL;
    aux = 1;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(int k = 0; k < n ; k++) {
                if(matrix[j][i] == 0) {
                    qtd_zeros_coluna += 1;
                    aux++;
                }
            break;
            }
        }
        indice_zeros_coluna = realloc(indice_zeros_coluna, aux * sizeof(int));
        indice_zeros_coluna[i] = qtd_zeros_coluna;
        qtd_zeros_coluna = 0;
    }




    printf("\n");
    for(i = 0; i < 4; i++) {
        printf("%d ", indice_zeros[i]);
    }
    printf("\n");

    printf("\n");
    for(i = 0; i < 4; i++) {
        printf("%d ", indice_zeros_coluna[i]);
    }
    printf("\n");

    printMat(mat, 4);

    return 0;

}



int main( ) {

    int matriz[4][4] = {{0,2,4,3}, {2,0,0,3}, {0,6,8,2}, {2,0,0,0}};

    printMat(matriz, 4);
    indice_dos_zeros(matriz, 4);

    cobrimento(matriz, 4);

    return 0;
}



