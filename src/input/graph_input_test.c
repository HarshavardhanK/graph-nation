#include "graph_input.h"

int main(int argc, char** argv) {

    if(argc < 2) {
        return 1;
    }

    int vertices = count_vertices(argv[1]);
    int edges = count_edges(argv[1]);

    printf("%d %d\n", vertices, edges);

    //read_line(argv[1]);

    Graph* graph = input_graph(argv[1]);

    return 0;
}