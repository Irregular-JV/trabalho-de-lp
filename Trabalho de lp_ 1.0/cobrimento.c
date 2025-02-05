#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4

//Struct para marcar os zeros de forma booleana
typedef struct {
    bool linha[N];
    bool coluna[N];
} marca_zeros;


//Função para criar zeros adicionais
void designar_zeros(int matrix[4][4], int n, int *indice_zeros_linha, int *indice_zeros_coluna);
int cobrimento(int matriz[N][N], int tam, int *indice_zeros_linha, int *indice_zeros_coluna);


//Função para imprimir a matriz
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



//Main-----------------------------------------------------------------------------------------------------------------------------------------------
int main() {
    // Array dos indices de zeros designados
    int *indice_zeros_linha, *indice_zeros_coluna;

    indice_zeros_linha = malloc(N * sizeof(int));
    indice_zeros_coluna = malloc(N * sizeof(int));

    //Matriz de teste 
    int matriz[4][4] = {
        {0,2,4,3}, 
        {2,0,0,3}, 
        {0,6,8,2}, 
        {2,0,0,0}};

    //Imprimindo a matriz
    printMat(matriz, 4);

    //Função que designa os zeros
    designar_zeros(matriz, 4, indice_zeros_linha, indice_zeros_coluna);

    printf("\nzeros designados\n");

    //Imprimindo os zeros designados
    for(int i = 0; i <  N; i++) {
        printf("%d", indice_zeros_linha[i]);
        printf("%d ", indice_zeros_coluna[i]);
    } 

    printf("\n");
    printf("\n");
    printf("\n");

    //Função de cobrimento
    cobrimento(matriz, 4, indice_zeros_linha, indice_zeros_coluna);


    return 0;
}

//Fim do main-------------------------------------------------------------------------------------------------------------------------------------



void designar_zeros(int matrix[4][4], int n, int *indice_zeros_linha, int *indice_zeros_coluna) {
    
    //Vetor para armazenar os indices dos zeros
    bool colunas_de_zeros_verificados[n];

    //Inicializando os vetores
    for (int i =0; i < n; i++) {
        *(indice_zeros_linha + i) = -1;
        *(indice_zeros_coluna + i) = -1;
        colunas_de_zeros_verificados[i] = false;
    }

    //Verificando os zeros designados
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 0 && !colunas_de_zeros_verificados[j]) {
                *(indice_zeros_linha + i) = i;
                *(indice_zeros_coluna + i) = j;
                colunas_de_zeros_verificados[j] = true;
                break;
            }
        }

    }
    
}


// Fazendo a cobertura dos zeros
int cobrimento(int matriz[N][N], int tam, int *indice_zeros_linha, int *indice_zeros_coluna){
    //Inicializando a struct
    marca_zeros marca;

    //Inicializando os vetores de marcação booleana
    for(int i = 0; i < tam; i++){
        marca.linha[i] = false;
        marca.coluna[i] = false;
    }

    // Fazer uma cópia da matriz dinamicamente
    int **mat = NULL;
    mat = malloc(tam * sizeof(int*));

    //Preenchendo a matriz
    for(int i = 0; i < tam; i++) {
        mat[i] = malloc(tam * sizeof(int));
        for(int j = 0; j < tam; j++) {
            mat[i][j] = matriz[i][j];
        }
    }

    //Passo a)
    //Marcar todas as linhas sem nenhum zero designado.
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++){
            if(indice_zeros_linha[i] == -1) {
                marca.linha[i] = true;
                break;
            }
        }
    }

    // //Passo b)
    // //Nas linhas marcadas, marcar todas as colunas que contêm zeros.
    // for(int i = 0; i < tam; i++) {
    //     if(marca.linha[i]) {
    //         for(int j = 0; j < tam; j++) {
    //             if(mat[i][j] == 0) {
    //                 marca.coluna[j] = true;
    //             }
    //         }
    //     } 
    // }

    // //Passo c)
    // //Nas colunas marcadas, marcar todas as linhas que contêm zeros designados.
    // for(int i = 0; i < tam; i++) {
    //     if(marca.coluna[i]) {
    //         for(int j = 0; j < tam; j++) {
    //             if(indice_zeros_coluna[j] == i) {
    //                 marca.linha[j] = true;
    //             }
    //         }
    //     }
    // }

    //Passo d)
    //Repetir os passos b) e c) até que não seja possível marcar mais linhas ou colunas.
    bool flag = true;
    while(flag) {
        flag = false;
        for(int i = 0; i < tam; i++) {
            if(marca.linha[i]) {
                for(int j = 0; j < tam; j++) {
                    if(mat[i][j] == 0 && !marca.coluna[j]) {
                        marca.coluna[j] = true;
                        flag = true;
                    }
                }
            }
        }

        for(int i = 0; i < tam; i++) {
            if(marca.coluna[i]) {
                for(int j = 0; j < tam; j++) {
                    if(indice_zeros_coluna[j] == i && !marca.linha[j]) {
                        marca.linha[j] = true;
                        flag = true;
                    }
                }
            }
        }
    }
    
    //Cobrir com -1 as linhas não marcadas e as colunas marcadas
    for(int i = 0; i < tam; i++) {
        if(!marca.linha[i]) {
            for(int j = 0; j < tam; j++) {
                mat[i][j] = -1;
            }
        }
    }


    for(int i = 0; i < tam; i++) {
        if(marca.coluna[i]) {
            for(int j = 0; j < tam; j++) {
                mat[j][i] = -1;
            }
        }
    }

    //Imprimindo a matriz
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");
    printf("\n");

    //Imprimindo os numeros não marcados
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            if(mat[i][j] != -1) {
                printf("%d ", mat[i][j]);
            }
        }
    }


    //5 passo - Redução adicional na matriz
    //a) -> Subtrair o menor elemento que não foi marcado de todas os elementos não marcadas

    //Encontrando o menor elemento que não foi marcado
    int menor = 1000;
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            if(mat[i][j] != -1 && mat[i][j] < menor) {
                menor = mat[i][j];
            }
        }
    }

    //Subtraindo o menor elemento que não foi marcado de todas os elementos não marcadas
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            if(mat[i][j] != -1) {
                mat[i][j] -= menor;
            }
        }
    }

    printf("\nMenor: %d\n", menor);

    // Matriz após a redução adicional
    printf("\nMatriz após a redução adicional\n");
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    //passo b)
    //Somar o elemento menor nas células que são intersecções ou seja nos que foram riscados 2 vezes
    

    return 0;

}