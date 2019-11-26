#ifndef UNION_FIND_H
#define UNION_FIND_H

struct subset {
    int rank;
    int parent;
};

typedef struct subset Subset;

int find(Subset* subsets, int index) {

    if(subsets[index].parent != index) {
        subsets[index].parent = find(subsets, subsets[index].parent);
    }

    return subsets[index].parent;
}

void _union(Subset* subsets, int x_set, int y_set) {

    int x_root = find(subsets, x_set);
    int y_root = find(subsets, y_set);

    if(subsets[x_root].rank < subsets[y_root].rank) {
        subsets[x_root].parent = y_root;

    } else if(subsets[x_root].rank > subsets[y_root].rank) {
        subsets[y_root].parent = x_root;

    } else {
        subsets[y_root].parent = x_root;
        subsets[x_root].rank++;
    }
}

#endif