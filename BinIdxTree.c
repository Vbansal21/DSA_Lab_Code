#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int* tree;
} BIT;

BIT* createBIT(int size) {
    BIT* bit = (BIT*)malloc(sizeof(BIT)); bit->size = size;
    bit->tree = (int*)calloc(size +1, sizeof(int)); return bit;
}

void updateBIT(BIT* bit, int index, int val) {
    while(index <= bit->size) { bit->tree[index] += val; index += index & -index; }
}

int queryBIT(BIT* bit, int index) {
    int sum =0; while(index >0) { sum += bit->tree[index]; index -= index & -index; }
    return sum;
}

int main(){
    int size = 10; BIT* bit = createBIT(size);
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
    updateBIT(bit, 3, 5); updateBIT(bit, 5, 3);
    printf("Sum up to 5: %d\n", queryBIT(bit,5));
    printf("Sum up to 3: %d\n", queryBIT(bit,3));
    free(bit->tree); free(bit);
    return 0;
}