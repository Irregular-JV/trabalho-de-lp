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
void designar_zeros(int **matrix, int n, int *indice_zeros_linha, int *indice_zeros_coluna);
int cobrimento(int **matriz, int tam, int *indice_zeros_linha, int *indice_zeros_coluna);


//Função para imprimir a matriz
void printMat(int **matrix, int n) {
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

    //Reservando memória para os indices designados
    indice_zeros_linha = malloc(N * sizeof(int));
    indice_zeros_coluna = malloc(N * sizeof(int));

    //Matriz de teste 
    int matriz[4][4] = {
        {13,14,0,8}, 
        {40,0,12,40}, 
        {6,64,0,66}, 
        {0,1,90,0}};

    
    int **matriz_dinan = malloc(N * sizeof(int*));

    for(int i = 0; i< N; i++) {
        matriz_dinan[i] = malloc(N * sizeof(int));
        for (int j = 0; j< N; j++) {
            matriz_dinan[i][j] = matriz[i][j];
        }
    }

    //Função que designa os zeros
    designar_zeros(matriz_dinan, 4, indice_zeros_linha, indice_zeros_coluna);

    //Função de cobrimento
    cobrimento(matriz_dinan, 4, indice_zeros_linha, indice_zeros_coluna);


    return 0;
}

//Fim do main-------------------------------------------------------------------------------------------------------------------------------------



void designar_zeros(int **matrix, int n, int *indice_zeros_linha, int *indice_zeros_coluna) {
    
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
int cobrimento(int **matriz, int tam, int *indice_zeros_linha, int *indice_zeros_coluna){
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

    //Passo b)
    //Nas linhas marcadas, marcar todas as colunas que contêm zeros.

    //Passo c)
    //Nas colunas marcadas, marcar todas as linhas que contêm zeros designados.

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
    printMat(mat, tam);

    printf("\n");

    //Imprimindo os numeros não marcados
    printf("Numeros nao marcados: ");
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
    printf("\nMatriz apos a reducao adicional\n");
    printMat(mat, tam);

    //passo b)
    //Somar o elemento menor nas células que são intersecções ou seja nos que foram riscados 2 vezes
    //1) Recolocar os números que foram riscados
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            if(mat[i][j] == -1) {
                mat[i][j] = matriz[i][j];
            }
        }

    }

    //Encontrar os números diferentes de 0 marcados 2 vezes
    for(int i = 0; i< tam; i++) {
        if(!marca.linha[i]) {
            for(int j = 0; j< tam; j++) {
                if(marca.coluna[j] && mat[i][j] != 0) {
                    mat[i][j] += menor;
                }
            }
        }
    }

    printf("\nMatriz depois de recolocar os numeros e somar o menor nas interccoes \n");
    printMat(mat, tam);

    printf("\n");

    // Por fim só designar novamente os zeros
    designar_zeros(mat, tam,indice_zeros_linha, indice_zeros_coluna);

    // Imprimir os indices dos zeros designados
    printf("Indices dos zeros designados: ");
    for(int i = 0; i < tam; i++) {
        printf("%d", *(indice_zeros_linha + i));
        printf("%d ", *(indice_zeros_coluna + i));
    }

    return 0;

}