#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "queue.h"
#include "stack.h"

#define INFINITY 999

#define UNDDIRECTED 0
#define DIRECTED 1

typedef int direction;

/*Three types of graph representation

    Undirected

    1. Adjacency list
    2. Edge list representation
    3. Adjacency matrix

    Directed
    1. Adjacency list
    2. Adjacency matrix

*/

//Adjacency list

struct adj_list_node {
    int dest;
    int weight;
    struct adj_list_node* next;
};

typedef struct adj_list_node ADJ_node;

struct adj_list {
    ADJ_node* head;
};

typedef struct adj_list ADJ_list;

struct graph_ {

    int vertices;
    ADJ_list* array;

    direction type;
};

typedef struct graph_ Graph;

ADJ_node* create_adj_node(int dest, int weight) {

    ADJ_node* node = (ADJ_node*) malloc(sizeof(ADJ_node));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;

    return node;
}

Graph* create_graph(int vertices, direction type) {

    Graph* graph = (Graph*) malloc(sizeof(graph));
    graph->vertices = vertices;
    graph->array = (ADJ_list*) malloc(sizeof(ADJ_list) * vertices);
    graph->type = type;

    for(int i = 0; i < vertices; i++)
        graph->array[i].head = NULL;

    return graph;
}

//---------------------------------------------------Repesentations-------------------------------------------------

//Adjacency Matrix

void print_graph_mat(int** mat, int size) {

    printf("adjacency matrix\n");

    for(int i = 0; i < size; i++) {

        for(int j = 0; j < size; j++) {

            if(mat[i][j] != INFINITY)
                printf("%d\t", mat[i][j]);

            else
                printf("INF\t");
        }

        printf("\n");
    }
}

void adj_to_mat(Graph* graph, int** mat, int non_connect) {

    printf("Converting list to matrix..\n");

    for(int i = 0; i < graph->vertices; i++) {

        for(int j = 0; j < graph->vertices; j++) {
            mat[i][j] = non_connect;
        }

        mat[i][i] = 0;
    }

    for(int i = 0; i < graph->vertices; i++) {

        ADJ_node* iter = graph->array[i].head;

        while(iter) {
            mat[i][iter->dest] = iter->weight;
            iter = iter->next;
        }
    }

}

//Edge list
struct edge_node {

    int src;
    int dest;
    int weight;

};

typedef struct edge_node Edge;

Edge* create_edge(int src, int dest, int weight) {

    Edge* edge = (Edge*) malloc(sizeof(Edge));
    edge->src = src;
    edge->dest = dest;
    edge->weight = weight;

    return edge;
}

struct edge_graph {

    int vertices;
    int edges;

    Edge** edge_list;
};

typedef struct edge_graph EGraph;

EGraph* init_egraph(int vertices) {

    EGraph* graph = (EGraph*) malloc(sizeof(EGraph));

    graph->vertices = vertices;
    graph->edges = 0;

    graph->edge_list = (Edge**) malloc(sizeof(Edge*) * vertices * vertices); //max edges

    return graph;

}

EGraph* graph_to_edge_graph(Graph* graph) {

    EGraph* egraph = init_egraph(graph->vertices);

    for(int i = 0; i < graph->vertices; i++) {

        ADJ_node* iter = graph->array[i].head;

        while(iter) {

            Edge* edge = create_edge(i, iter->dest, iter->weight);

            egraph->edge_list[egraph->edges++] = edge;

            iter = iter->next;
        }
    }

    return egraph;
}

void print_edge_graph(EGraph* graph) {

    printf("Edge list representation\n");

    for(int i =0; i < graph->edges; i++) {
        printf("%d --> %d w: %d\n", graph->edge_list[i]->src, graph->edge_list[i]->dest, graph->edge_list[i]->weight);
    }

    printf("\n");
}

void print_edges(Edge** edge_list, int size) {

    printf("Edge list\n");

    for(int i =0; i < size; i++) {
        printf("%d --> %d w: %d\n", edge_list[i]->src, edge_list[i]->dest, edge_list[i]->weight);
    }

    printf("\n");
}

void add_edge(Graph* graph, int src, int dest, int weight) {

    ADJ_node* node = create_adj_node(dest, weight);

    node->next = graph->array[src].head;
    graph->array[src].head = node;

    if(graph->type == UNDDIRECTED) {

        ADJ_node* dest_node = create_adj_node(src, weight);

        dest_node->next = graph->array[dest].head;
        graph->array[dest].head = dest_node;

    }

}

void print_graph(Graph* graph) {

    for(int i = 0; i < graph->vertices; i++) {

        ADJ_node* iter = graph->array[i].head;

        printf("ADJ List of vertex %d\n Head", i);

        while(iter) {

            printf("-> %d", iter->dest);
            iter = iter->next;

        }

        printf("\n");
    }
}

Queue* bfs(Graph* graph, int start) {

    if(!graph) {
        printf("Graph error bfs\n");
        return NULL;
    }

    int visited[graph->vertices];

    memset(visited, 0, sizeof(visited));

    visited[start] = 1;

    Queue* queue = init_queue(graph->vertices);
    enqueue(queue, start);

    Queue* bfs_queue = init_queue(graph->vertices);
    enqueue(bfs_queue, start);

    while(!is_empty(queue)) {

        int dat = dequeue(queue);
        ADJ_node *node = graph->array[dat].head;

        while(node != NULL) {

            if(!visited[node->dest]) {
                enqueue(queue, node->dest);
                visited[node->dest] = 1;

                enqueue(bfs_queue, node->dest);

            }
                
            node = node->next;
        }

    }

    return bfs_queue;

    printf("\n");
}

//DSF
Queue* dfs(Graph* graph, int start) {

    int visited[graph->vertices];
    memset(visited, 0, sizeof(visited));

    Stack* stack = init_stack(graph->vertices);
    push(stack, start);

    Queue* result = init_queue(graph->vertices);

    visited[start] = 1;
    enqueue(result, start);

    while(!stack_empty(stack)) {

        int node_data = pop(stack);
    
        if(node_data != -1) {

            ADJ_node* node = graph->array[node_data].head;

            while(node) {

                if(!visited[node->dest]) {

                    enqueue(result, node->dest);
                  
                    push(stack, node->dest);
                    visited[node->dest] = 1;

                }
                
                node = node->next;

            }

        } else {
            break;
        }

    }

    return result;
}

Queue* topological_sort(Graph* graph) {

    //returns a list of nodes in the topological order

    Queue* result = init_queue(graph->vertices);
    Queue* queue = init_queue(graph->vertices);

    int visited[graph->vertices];
    memset(visited, 0, sizeof(visited));

    int in_degree[graph->vertices];
    memset(in_degree, 0, sizeof(in_degree));

    int** mat = (int**) malloc(sizeof(int*) * graph->vertices);

    for(int i = 0; i < graph->vertices; i++)
        mat[i] = (int*) malloc(sizeof(int) * graph->vertices);

    //convert adjacency list to matrix
    adj_to_mat(graph, mat, 0);

    for(int i = 0; i < graph->vertices; i++) {

        for(int j = 0; j < graph->vertices; j++) {

            if(mat[i][j] != 0) {
                in_degree[j]++;
            }
        }

    }

    for(int i = 0; i < graph->vertices; i++) {

        //if in-degree is 0, add it to the result array

        if(in_degree[i] == 0) {
            enqueue(queue, i);
            visited[i] = 1;
        }
    }

    while(!is_empty(queue)) {

        int vertex = dequeue(queue);

        enqueue(result, vertex);

        for(int i = 0; i < graph->vertices; i++) {

            if(mat[vertex][i] && !visited[i]) {
                in_degree[i]--;

                if(in_degree[i] == 0) {
                    enqueue(queue, i);
                    visited[i] = 1;
                }

            }

        }
    }

    return result;
}

//DIJSKTRA

int min(int a, int b) {
    return a < b ? a : b;
}

int min_dist(int* dist, int vertices, int* visited) {

    int min = INT_MAX;
    int min_index = INT_MAX;

    for(int i = 0; i < vertices; i++) {
        if(dist[i] < min && !visited[i]) {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void disjkstra(Graph* graph, int source, int *result) {

    if(source > graph->vertices || source < 0) {
        printf("Invalid source\n");
        return;
    }

    printf("Running Dijkstra's algorithm\n");

    int** mat = (int**) malloc(sizeof(int*) * graph->vertices);

    for(int i = 0; i < graph->vertices; i++)
        mat[i] = (int*) malloc(sizeof(int) * graph->vertices);

    adj_to_mat(graph, mat, INFINITY);

    int *dist = (int*) malloc(sizeof(int) * graph->vertices);

    for(int i = 0; i < graph->vertices; i++)
        dist[i] = mat[source][i];

    int *visited = (int*) malloc(sizeof(int) * graph->vertices);

    for(int i = 0; i < graph->vertices; i++)
        visited[i] = 0;

    visited[source] = 1;

    for(int i = 0; i < graph->vertices - 2; i++) {

        int u = min_dist(dist, graph->vertices, visited);
        visited[u] = 1;

        for(int v = 0; v < graph->vertices; v++) {

            if(!visited[v]) {

                if(dist[v] > dist[u] + mat[u][v]) {
                    dist[v] = dist[u] + mat[u][v];
                }
            }
        }

    }

    for(int i = 0; i < graph->vertices; i++)
        result[i] = dist[i];
}

//Kruskal MST

#include "union_find.h"

int compare_edges(const void* e1, const void* e2) {
    return ((Edge*)e1)->weight > ((Edge*)e2)->weight;
}

Edge** mst(Graph* graph) {

    EGraph* egraph = graph_to_edge_graph(graph);
    int edge_counter = 0;

    Edge** result = (Edge**) malloc(sizeof(Edge*) * egraph->edges);
    int result_counter = 0;

    qsort(egraph->edge_list, egraph->edges, sizeof(egraph->edge_list[0]), compare_edges);

    Subset* subsets = (Subset*) malloc(sizeof(Subset) * egraph->vertices);

    for(int i = 0; i < egraph->vertices; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    while(result_counter < egraph->vertices - 1 && edge_counter < egraph->edges - 1) {

        Edge* next = egraph->edge_list[edge_counter++];

        int src_set = find(subsets, next->src);
        int dest_set = find(subsets, next->dest);

        if(src_set != dest_set) {
            result[result_counter++] = next;
            _union(subsets, src_set, dest_set);

        }

    }


    return result;

}


//BIPARTITE


int is_bipartite(Graph* graph) {

    int color[graph->vertices];
    memset(color, -1, sizeof(color));

    int max_edges = graph->vertices * graph->vertices;

    //Assume source to be the 0th vertice
    int source = 0;

    color[source] = 1;

    Queue* queue = init_queue(max_edges);
    enqueue(queue, source);

    int **mat = (int**) malloc(sizeof(int*) * graph->vertices);

    for(int i = 0; i < graph->vertices; i++)
        mat[i] = (int*) malloc(sizeof(int) * graph->vertices);

    adj_to_mat(graph, mat, 0);

    while(!is_empty(queue)) {

        int u = dequeue(queue);

        for(int v = 0; v < graph->vertices; v++) {

            if(mat[u][v] && color[v] == -1) {
                //not colored
                color[v] = 1 - color[u];
                enqueue(queue, v);

            } else if(mat[u][v] && color[u] == color[v]) {
                return 0;
            }

        }
    }

    return 1;
}

//---------------------------------------Generate graphs-------------------------------
Graph* bipartite_graph() {

    Graph* graph = create_graph(7, UNDDIRECTED);

    add_edge(graph, 0, 1, 3); 
    add_edge(graph, 0, 3, 11); 
    add_edge(graph, 0, 5, 4); 
    add_edge(graph, 0, 7, 1); 
    add_edge(graph, 1, 2, 5); 
    add_edge(graph, 1, 4, 6); 
    add_edge(graph, 1, 6, 9);
    add_edge(graph, 2, 5, 8);
    add_edge(graph, 2, 7, 3);
    add_edge(graph, 4, 5, 5); 
    add_edge(graph, 6, 7, 6); 
    add_edge(graph, 3, 4, 9);
    add_edge(graph, 3, 6, 8);
    

    return graph;

}

Graph* normal_graph() {

    Graph* graph = create_graph(7, UNDDIRECTED);
    add_edge(graph, 0, 1, 3); 
    add_edge(graph, 0, 4, 11); 
    add_edge(graph, 1, 2, 4); 
    add_edge(graph, 1, 3, 1); 
    add_edge(graph, 1, 4, 5); 
    add_edge(graph, 2, 3, 6); 
    add_edge(graph, 3, 4, 9);
    add_edge(graph, 4, 5, 8);
    add_edge(graph, 5, 6, 3);

    return graph;
}

Graph* directed_graph() {

    Graph* graph = create_graph(7, DIRECTED);
    add_edge(graph, 0, 1, 3); 
    add_edge(graph, 0, 4, 11); 
    add_edge(graph, 1, 2, 4); 
    add_edge(graph, 1, 3, 1); 
    add_edge(graph, 1, 4, 5); 
    add_edge(graph, 2, 3, 6); 
    add_edge(graph, 3, 4, 9);
    add_edge(graph, 4, 5, 8);
    add_edge(graph, 5, 6, 3);

    return graph;
}



#endif