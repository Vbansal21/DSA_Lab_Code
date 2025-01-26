#include <stdio.h>
#include <stdlib.h>

int getMid(int s, int e) { return s + (e -s)/2; }

int* createSegmentTree(int n) {
    int x = (int)(ceil(log2(n)));

    int max_size = 2*(int)pow(2, x) -1;

    int* tree = (int*)malloc(max_size * sizeof(int));
    if(!tree) {
        printf("Memory allocation error\n");
        exit(1);
    }
    return tree;
}

int buildSegmentTree(int arr[], int* tree, int start, int end, int index) {
    if(start == end) {
        tree[index] = arr[start];
        return tree[index];
    }

    int mid = getMid(start, end);
    tree[index] = buildSegmentTree(arr, tree, start, mid, 2*index+1) +
                  buildSegmentTree(arr, tree, mid+1, end, 2*index+2);
    return tree[index];
}

void updateValueUtil(int arr[], int* tree, int start, int end, int idx, int value, int treeIndex) {
    if(start == end) {
        arr[idx] = value;
        tree[treeIndex] = value;
        return;
    }

    int mid = getMid(start, end);
    if(idx <= mid)
        updateValueUtil(arr, tree, start, mid, idx, value, 2*treeIndex+1);
    else
        updateValueUtil(arr, tree, mid+1, end, idx, value, 2*treeIndex+2);

    tree[treeIndex] = tree[2*treeIndex+1] + tree[2*treeIndex+2];
}

int getSumUtil(int* tree, int start, int end, int l, int r, int index) {
    if(l <= start && r >= end)
        return tree[index];

    if(end < l || start > r)
        return 0;

    int mid = getMid(start, end);
    return getSumUtil(tree, start, mid, l, r, 2*index+1) +
           getSumUtil(tree, mid+1, end, l, r, 2*index+2);
}

void updateValue(int arr[], int* tree, int n, int idx, int value) {
    if(idx < 0 || idx >= n) {
        printf("Invalid index\n");
        return;
    }

    updateValueUtil(arr, tree, 0, n-1, idx, value, 0);
    printf("Updated index %d to value %d.\n", idx, value);
}

int getSum(int* tree, int n, int l, int r) {
    if(l < 0 || r > n-1 || l > r) {
        printf("Invalid range\n");
        return -1;
    }
    return getSumUtil(tree, 0, n-1, l, r, 0);
}

void printSegmentTree(int* tree, int size) {
    printf("Segment Tree: ");
    for(int i = 0; i < size; i++)
        printf("%d ", tree[i]);
    printf("\n");
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);

    int* tree = createSegmentTree(n);
    buildSegmentTree(arr, tree, 0, n-1, 0);
    printSegmentTree(tree, 2*(int)pow(2, (int)ceil(log2(n))) -1);

    printf("Sum of values in range [1, 3] is %d\n", getSum(tree, n, 1, 3));

    updateValue(arr, tree, n, 1, 10);
    printSegmentTree(tree, 2*(int)pow(2, (int)ceil(log2(n))) -1);

    printf("Sum of values in range [1, 3] after update is %d\n", getSum(tree, n, 1, 3));

    free(tree);
    return 0;
}