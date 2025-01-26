#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int parent;
    int rank;
} DisjointSet;

DisjointSet* makeSet(int n) {
    DisjointSet* ds = (DisjointSet*)malloc(n * sizeof(DisjointSet));
    for(int i=0; i<n; i++) { ds[i].parent = i; ds[i].rank = 0; }
    return ds;
}

int findSet(DisjointSet* ds, int x) {
    if(ds[x].parent != x) ds[x].parent = findSet(ds, ds[x].parent);
    return ds[x].parent;
}

void unionSet(DisjointSet* ds, int x, int y) {
    int xroot = findSet(ds, x); int yroot = findSet(ds, y);
    if(xroot == yroot) return;
    if(ds[xroot].rank < ds[yroot].rank) ds[xroot].parent = yroot;
    else if(ds[xroot].rank > ds[yroot].rank) ds[yroot].parent = xroot;
    else { ds[yroot].parent = xroot; ds[xroot].rank +=1; }
}

int main(){
    int n = 5; DisjointSet* ds = makeSet(n);
    unionSet(ds, 0, 2); unionSet(ds, 4, 2); unionSet(ds, 3, 1);
    for(int i=0; i<n; i++) printf("Parent of %d: %d\n", i, findSet(ds, i));
    free(ds);
    return 0;
}