// Aprendendo a usar grafos em C
/*
    Um grafo é uma estrutura de dados que consiste em um conjunto de vértices (ou nós) e um conjunto de arestas que conectam pares de vértices.
    --> Vértices (nós): Representam pontos ou entidades (ex: cidades, pessoas).
    --> Arestas: Conectam pares de vértices, representando relações (ex: estradas, amizades).
    --> Grafo direcionado: As arestas têm uma direção (ex: A → B).
    --> Grafo não-direcionado: As arestas não têm direção (ex: A — B).
    --> Ponderado: Cada aresta tem um peso (ex: distância, custo).
    --> Não-ponderado: Não há pesos, apenas conexões.


    Representação de grafos
    --> Matriz de adjacência: Uma matriz quadrada onde o elemento (i, j) é 1 se há uma aresta de i para j, e 0 caso contrário.
    --> Lista de adjacência: Para cada vértice, uma lista de seus vizinhos (vértices conectados por uma aresta).

    --> Lista de adjacência é mais eficiente para grafos esparsos (poucas arestas).


 */


// Criando um grafo com matriz de adjacência
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 4
/*
int main() {
    // Criando a matriz de adjacência
    int grafo[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };


    //Exibindo as conexões entre as cidades
    printf("Conexões entre as cidades:\n");

    for(int i = 0; i < MAX_VERTICES; i++) {
        for(int j = 0; j <MAX_VERTICES; j++) {
            if(grafo[i][j] == 1) {
                printf("Cidade %d esta conectada com a cidade %d\n", i, j);
            }
        }
    }

    return 0;


}
*/

//Algoritimo de busca BFS - Visitar primeiro todos os vizinhos de um vértice antes de visitar os vizinhos dos vizinhos.
//Utiliza uma fila para armazenar os vértices a serem visitados.

/*
//Fila para armazenar os vértices a serem visitados
    struct fila{
        int itens[MAX_VERTICES];
        int frente, tras;
    };


int main() {

    //BFS é im algoritimo de busca que explora o grafo por camadas
    //Começa pelo vértice inicial, visita todos os vizinhos desse vértice, depois visita os vizinhos dos vizinhos e assim por diante.

    /*
    Grafo:
          0
         / \
        1   2
        \   /
          3 

        --> A conexão de arestas são: (0,1),(0,2),(1,3),(2,3)

     */

    //Aplique o algoritimo BFS para visitar todos os vértices do grafo.

    // Inicializa a fila*/

    // DFS - Depth First Search - Busca em profundidade

    int grafo[MAX_VERTICES][MAX_VERTICES]; // Matriz de adjacência
    bool visitados[MAX_VERTICES];          // Vértices visitados
    int numero_vertices;                   // Número de vértices no grafo


    // Função para visitar um vértice e seus vizinhos

    void dfs(int v) {
        printf("Visitando vértice %d\n", v); // Exibe o vértice visitado
        visitados[v] = true; // Marca o vértice como visitado

        // Visita todos os vizinhos do vértice v
        for(int i = 0; i < numero_vertices; i++) {
            if(grafo[v][i] && !visitados[i]) { // Se i é vizinho de v e não foi visitado
                dfs(i); // Visita o vértice i
            }
        }
    }


int main() {
    int numArestas;
    scanf("%d", &numero_vertices);

    //Inicializa a matriz de adjacência e o vetor de visitados
    for(int i = 0 ; i < numero_vertices; i++) {
        visitados[i] = false;
        for(int j = 0; j < numero_vertices; j++) {
            grafo[i][j] = 0;
        }
    }


    //Lê as arestas do grafo
    printf("Digite o número de arestas: ");
    scanf("%d", &numArestas);

    //Digite as conecções entre os vértices
    for(int i = 0; i < numArestas; i++) {
        int origem, destino;
        printf("Digite a aresta %d (u, v): ", i + 1);
        scanf("%d %d", &origem, &destino);
        grafo[origem][destino] = 1; // para grafo direcionado
        grafo[destino][origem] = 1; // Remove essa linha para grafo não-direcionado
    }

    printf("Digite o vértice inicial para a busca em profundidade: ");
    int vertice_inicial;
    scanf("%d", &vertice_inicial);

    printf("Busca em profundidade a partir do vértice %d:\n", vertice_inicial);
    dfs(vertice_inicial);
    printf("\n");

}

