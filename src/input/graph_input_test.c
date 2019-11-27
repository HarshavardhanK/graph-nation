#include "graph_input.h"

void user_input_formatting(char** argv) {

    printf("Usage\n");

    printf("./graph.sh [graph_csv_file.csv] -alg -[options]\n");

    printf("-[options] are given as \n");

    printf("-dij for Dijkstra's algorithm\n");
    printf("-bfs for bread-first search\n");
    printf("-dfs for depth-first search\n");
    printf("-mst for Kruskal's minimum spanning tree\n");

    char continue_ = 'n';

    printf("Do you want to see more options? [y/n]");

    scanf("%c", &continue_);

    if(continue_ == 'n')
        return;
    
    //add more algorithms

    // when the shell script is run, graphviz shows the graph first, and waits for the user to continue running the algorithm..

}

int main(int argc, char** argv) {

    if(argc < 2) {
        return 1;
    }

    int vertices = count_vertices(argv[1]);
    int edges = count_edges(argv[1]);

    Graph* graph = input_graph(argv[1]);

   int* result = (int*) malloc(sizeof(int) * vertices);

   disjkstra(graph, 0, result);

   for(int i = 0; i < vertices; i++) 
        printf("%d ", result[i]);

    printf("\n");

    return 0;
}