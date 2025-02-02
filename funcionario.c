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
    int *indice_zeros_linha = NULL;
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
        indice_zeros_linha = realloc(indice_zeros_linha, aux * sizeof(int));
        indice_zeros_linha[i] = qtd_zeros_linha;
        qtd_zeros_linha = 0;
    }

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


    // Buscar qual do vetores tem a mauir quantidade de zeros
    int maior_zeros_linha = 0;
    int maior_zeros_coluna = 0;

    int menor_zeros_linha = 0;
    int menor_zeros_coluna = 0;
    int menor_zeros = 0;

    for(i = 0; i < 4; i++) {
        if(indice_zeros_linha[i] > maior_zeros_linha) {
            maior_zeros_linha = indice_zeros_linha[i];
        }
        if(indice_zeros_coluna[i] > maior_zeros_coluna) {
            maior_zeros_coluna = indice_zeros_coluna[i];
        }

        if(indice_zeros_linha[i] < menor_zeros_linha) {
            menor_zeros_linha = indice_zeros_linha[i];
        }

        if(indice_zeros_coluna[i] < menor_zeros_coluna) {
            menor_zeros_coluna = indice_zeros_coluna[i];
        }
    }

    if(maior_zeros_linha > maior_zeros_coluna) {
        menor_zeros = maior_zeros_coluna;
    } else {
        menor_zeros = maior_zeros_linha;
    }

    // Verificar se a linha ou coluna tem mais zeros
    if (maior_zeros_linha > maior_zeros_coluna) {

        // Se o numero de zeros da linha for igual ao numero de zeros da colun, usa a linha

        for (int i = 0; i < n; i++) {
            if (indice_zeros_linha[i] >= menor_zeros) { // Deve ser >= para incluir todas as linhas que atendem a condição
                for(int j = 0; j <n; j++) {
                    mat[i][j] = -1; // Preenchendo corretamente as linhas
                }
            }
        }

        // Verificando as colunas com mais zeros e onde ja foi preenchido para passar o menor numero de retas
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(mat[i][j] == -1) {
                    for(int k = 0; k < n; k++) {
                        if(mat[k][j] == 0) {
                            mat[k][j] = -1;
                        }
                    }
                }
            }
        }

        // Se uma linha ou coluna tem -1 então um dos lados deve ta preenchido
        // com -1
        
        


    } else {
        for (int i = 0; i < n; i++) {
            if (indice_zeros_coluna[i] >= menor_zeros) { // Deve ser >= para incluir todas as linhas que atendem a condição
                for (int j = 0; j <n; j++) {
                    mat[j][i] = -1; // Preenchendo corretamente as colunas
                }
            }
        }

        // Verificando as linhas com mais zeros e onde ja foi preenchido para passar o menor numero de retas
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(mat[j][i] == -1) {
                    for(int k = 0; k < n; k++) {
                        if(mat[j][k] == 0) {
                            mat[j][k] = -1;
                        }
                    }
                }
            }
        }
    }

    


    



    printf("\nZeros da linha \n");
    for(i = 0; i < 4; i++) {
        printf("%d ", indice_zeros_linha[i]);
    }
    printf("\n");

    printf("\nZeros da coluna \n");
    for(i = 0; i < 4; i++) {
        printf("%d ", indice_zeros_coluna[i]);
    }
    printf("\n");

    // Matriz de cobrimento
    printMat(mat, 4);

    return 0;

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



