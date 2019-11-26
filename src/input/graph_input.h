#ifndef GRAPH_INPUT_H
#define GRAPH_INPUT_H

#define MAX_VERTICES 30

#include <stdio.h>
#include <stdlib.h>
#include "../graph/graph.h"

int count_vertices(char* file_name) {

    FILE* fp = fopen(file_name, "r");

    int vertices = 0;

    int vertice_list[256]; //assume max vertices of graph

    for(int i = 0; i < 256; i++)
        vertice_list[i] = 0;


    while(1) {

        char next = fgetc(fp);

        if(next == EOF)
            break;

        if(next != ',' && next != '\n' && next >= 65) 
            vertice_list[next] = 1;
        
    }

    for(int i = 0; i < 256; i++)
        vertices += vertice_list[i];

    return vertices;
}

int count_edges(char* file_name) {

    FILE* file = fopen(file_name, "r");

    int edges = 0;

    while(1) {
        char next = fgetc(file);

        if(next == '\n')
            edges++;

        if(next == EOF)
            break;
    }

    return ++edges;
}

void read_line(char* file_name) {

    FILE* file = fopen(file_name, "r");

    char* line = (char*) malloc(sizeof(char) * 10);
    size_t len = 0;

    while(getline(&line, &len, file) != -1) {
        printf("%s", line);
    }
}

Graph* input_graph(char* file_name) {

    int vertices = count_vertices(file_name);
    int edges = count_edges(file_name);

    Graph *graph = create_graph(vertices, UNDDIRECTED);

    if(vertices < 2) {
        printf("not a valid graph\n");
        return NULL;
    }

    FILE* graph_file = fopen(file_name, "r");

    char* line = (char*) malloc(sizeof(char) * 10);
    size_t len = 0;

    while(getline(&line, &len, graph_file) != -1) {
        printf("%d -> %d w: %d\n", line[0] - 65, line[3] - 65, line[6] - '0');
        add_edge(graph, line[0] - 65, line[3] - 65, line[6] - '0');
    }

    print_graph(graph);

    return graph;

}

#endif