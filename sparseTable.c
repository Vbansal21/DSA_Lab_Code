#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int n, log;
    int** table;
} SparseTable;

SparseTable* buildSparseTable(int* arr, int n) {
    SparseTable* st = (SparseTable*)malloc(sizeof(SparseTable));
    st->n = n; st->log = (int)log2(n) +1;
    st->table = (int**)malloc(st->log * sizeof(int*));
    for(int i=0;i<st->log;i++) st->table[i] = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) st->table[0][i] = arr[i];
    for(int j=1; j<st->log; j++) {
        for(int i=0; i + (1<<j) <=n; i++) {
            st->table[j][i] = st->table[j-1][i] < st->table[j-1][i + (1<<(j-1))] ? st->table[j-1][i] : st->table[j-1][i + (1<<(j-1))];
        }
    }
    return st;
}

int querySparseTable(SparseTable* st, int L, int R) {
    int j = (int)log2(R - L +1);
    return st->table[j][L] < st->table[j][R - (1<<j) +1] ? st->table[j][L] : st->table[j][R - (1<<j) +1];
}

void freeSparseTable(SparseTable* st) {
    for(int i=0;i<st->log;i++) free(st->table[i]);
    free(st->table); free(st);
}

int main(){
    int arr[] = {1,3,2,7,9,11,3,5,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    SparseTable* st = buildSparseTable(arr, n);
    printf("Min of [1,4]: %d\n", querySparseTable(st,1,4));
    printf("Min of [0,8]: %d\n", querySparseTable(st,0,8));
    freeSparseTable(st);
    return 0;
}