#include <stdio.h>
#include <stdlib.h>

typedef struct MinHeap {
    int* arr;
    int capacity;
    int size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size =0; heap->capacity = capacity; heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int* x, int* y) { int temp = *x; *x = *y; *y = temp; }

void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx, left =2*idx +1, right =2*idx +2;
    if(left < heap->size && heap->arr[left] < heap->arr[smallest]) smallest = left;
    if(right < heap->size && heap->arr[right] < heap->arr[smallest]) smallest = right;
    if(smallest != idx) { swap(&heap->arr[smallest], &heap->arr[idx]); heapifyDown(heap, smallest); }
}

void insertMinHeap(MinHeap* heap, int key) {
    if(heap->size == heap->capacity) return;
    heap->arr[heap->size] = key; int i = heap->size++;
    while(i !=0 && heap->arr[(i-1)/2] > heap->arr[i]) { swap(&heap->arr[i], &heap->arr[(i-1)/2]); i=(i-1)/2; }
}

int extractMin(MinHeap* heap) {
    if(heap->size <=0) return -1;
    if(heap->size ==1) return heap->arr[--heap->size];
    int root = heap->arr[0]; heap->arr[0] = heap->arr[--heap->size]; heapifyDown(heap,0); return root;
}

void displayHeap(MinHeap* heap) {
    for(int i =0; i < heap->size; i++) printf("%d ", heap->arr[i]);
    printf("\n");
}

void freeHeap(MinHeap* heap) { free(heap->arr); free(heap); }

int main() {
    MinHeap* heap = createMinHeap(10);
    insertMinHeap(heap, 10); insertMinHeap(heap, 20); insertMinHeap(heap, 5);
    insertMinHeap(heap, 30); insertMinHeap(heap, 2);
    displayHeap(heap);
    printf("Extracted min: %d\n", extractMin(heap));
    displayHeap(heap);
    insertMinHeap(heap, 1);
    displayHeap(heap);
    while(heap->size >0) { printf("Extracted min: %d\n", extractMin(heap)); displayHeap(heap); }
    freeHeap(heap);
    return 0;
}