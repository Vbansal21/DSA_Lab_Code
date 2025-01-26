#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size, capacity;
    int* dense;
    int* sparse;
} SparseSet;

SparseSet* createSparseSet(int capacity) {
    SparseSet* set = (SparseSet*)malloc(sizeof(SparseSet));
    set->size = 0; set->capacity = capacity;
    set->dense = (int*)malloc(capacity * sizeof(int));
    set->sparse = (int*)malloc(capacity * sizeof(int));
    return set;
}

int contains(SparseSet* set, int x) {
    if(x >= set->capacity) return 0;
    return set->dense[set->sparse[x]] == x && set->sparse[x] < set->size;
}

void insert(SparseSet* set, int x) {
    if(x >= set->capacity || contains(set, x)) return;
    set->dense[set->size] = x;
    set->sparse[x] = set->size;
    set->size++;
}

void removeElement(SparseSet* set, int x) {
    if(!contains(set, x)) return;
    int idx = set->sparse[x];
    int last = set->dense[set->size -1];
    set->dense[idx] = last;
    set->sparse[last] = idx;
    set->size--;
}

void displaySparseSet(SparseSet* set) {
    printf("Sparse Set: ");
    for(int i=0;i<set->size;i++) printf("%d ", set->dense[i]);
    printf("\n");
}

int main(){
    SparseSet* set = createSparseSet(10);
    insert(set, 3); insert(set, 5); insert(set, 7); insert(set, 9);
    displaySparseSet(set);
    removeElement(set,5); displaySparseSet(set);
    printf("Contains 7: %d\n", contains(set,7));
    printf("Contains 5: %d\n", contains(set,5));
    free(set->dense); free(set->sparse); free(set);
    return 0;
}