#ifndef GRAPH_H_
#define GRAPH_H_

#include "constants.h"

typedef struct Graph{
    int numPVertices;
    int numEVertices;
    struct Node **profList;
    struct Node **schoolList;
} Graph;

typedef struct Node {
    int vertex;
    //int weight;
    struct Node* next;
}Node;

/**
 * Cria um novo no, para encadear a lista de adjacencias
 * e retorna o endereço de memoria onde esta alocado
 */
Node* create_node(int v) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->vertex = v;
    newNode ->next = NULL;
    return newNode;
}

/**
 * Cria o grafo, inicializando todas as listas de adjacencias
 * com NULL, e retorna o endereço de memoria alocado para o grafo
 */
Graph* create_graph(int p_vertices, int s_vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numPVertices = p_vertices;
    graph->numEVertices = s_vertices;
    graph->profList = (Node**) malloc(p_vertices * sizeof(Node*));
    graph->schoolList = (Node**) malloc(s_vertices * sizeof(Node*));

    int i;
    for(i = 0; i < p_vertices; i++) {
        if(i < s_vertices) {
            graph->schoolList[i] = NULL;
        }
        graph->profList[i] = NULL;
    }

    return graph;

}

/**
 * Procura na lista de adjacencia do vertice pivo se já existe
 * o outro vertice que se deseja adicionar pois caso exista
 * nao sera possivel adicionar novamente este vertice
 */
int search_vertex(Graph* graph, int v, int w) {
    Node* list = graph->profList[v];
    while(list != NULL) {
        if(list->vertex == w) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

/**
 * Adiciona-se uma aresta ao grafo, como o grafo é não direcional
 * cria-se o segmento v->w e depois cria-se o w->v. Cria-se o no que apontara
 * para NULL após isso aponta-se o proximo elemento da lista para o
 */
void add_edge(Graph* graph, int v, int w) {
    if(!search_vertex(graph, v, w)) {
        Node* newNode = create_node(w);
        newNode->next = graph->profList[v];
        graph->profList[v] = newNode;

        newNode = create_node(v);
        newNode->next = graph->schoolList[w];
        graph->schoolList[w] = newNode;
    } else {
        printf("The graph already contains this edge!\n");
    }
}

/**
 * Realiza-se a impressão da lista de adjacencia na tela
 */
void print_graph(Graph* graph, char type) {
    int v;
    if(type == 'p') {
        for (v = 0; v < graph->numPVertices; v++) {
            Node* temp = graph->profList[v];
            printf("\n%d: ", v);
            while (temp) {
                printf("%d -> ", temp->vertex);
                temp = temp->next;
            }
            printf("\n");
        }
    }else {
        for (v = 0; v < graph->numEVertices; v++) {
            Node* temp = graph->schoolList[v];
            printf("\n%d: ", v);
            while (temp) {
                printf("%d -> ", temp->vertex);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

/**
 * Verifica se o grafo está vazio, verificando se todas as
 * listas de adjacencias estao vazias, caso contenha pelo menos 1
 * não vazia significa que o grafo não é vazio
*/
int is_graph_empty(Graph* graph) {
    int p_vertices = graph->numPVertices;
    int s_vertices = graph->numEVertices;

    int i;
    for(i = 0; i < p_vertices; i++) {
        if(graph->profList[i] != NULL || (i < s_vertices && graph->schoolList[i] != NULL)){
            return 0;
        }
    }

    return 1;
}

/**
 * Realiza a liberação da memoria alocada para o grafo, para isso
 * percorre-se todo o array de lista de adjacencias, liberando a memoria
 * alocada para os nos das listas, após todas as listas serem liberadas
 * finalmente libera-se o grafo
*/
void destroy_graph(Graph* graph) {
    int p_vertices = graph->numPVertices;
    int s_vertices = graph->numEVertices;

    int i;
    for(i = 0; i < p_vertices; i++) {
        Node* n = graph->profList[i];
        while(n != NULL){
            Node* temp = n->next;
            free(n);
            n = temp;
        }
        
    }

    for(i = 0; i < s_vertices; i++) {
        Node* n = graph->schoolList[i];
        while(n != NULL){
            Node* temp = n->next;
            free(n);
            n = temp;
        }
        
    }

    free(graph);
}

/**
 * Retorna os vertices adjacentes de um vertice dado v
 */
Node* neighbor_set(Graph* graph, int v, char type) {
    if(type == 'p')
        return graph->profList[v];
    else
        return graph->schoolList[v];

}

int get_list_size(Node* list) {
    Node* l = list;
    if(l == NULL) {
        return 0;
    }
    int size = 1;
    while(l->next != NULL) {
        size++;
        l = l->next;
    }
    //printf("%d", size);
    return size;
}

#endif