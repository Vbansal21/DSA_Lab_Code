#include <stdio.h>
#include <stdlib.h>

typedef struct MaxHeap {
    int* arr;
    int capacity;
    int size;
} MaxHeap;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(capacity * sizeof(int));
    return heap;
}

void swap(int* x, int* y) { int temp = *x; *x = *y; *y = temp; }

void heapify(MaxHeap* heap, int i) {
    int largest = i, left =2*i +1, right =2*i +2;
    if(left < heap->size && heap->arr[left] > heap->arr[largest])
        largest = left;
    if(right < heap->size && heap->arr[right] > heap->arr[largest])
        largest = right;
    if(largest != i) { swap(&heap->arr[i], &heap->arr[largest]); heapify(heap, largest); }
}

void insertHeap(MaxHeap* heap, int key) {
    if(heap->size == heap->capacity) return;
    heap->arr[heap->size] = key; int i = heap->size++;
    while(i !=0 && heap->arr[(i-1)/2] < heap->arr[i]) { swap(&heap->arr[i], &heap->arr[(i-1)/2]); i=(i-1)/2; }
}

int extractMax(MaxHeap* heap) {
    if(heap->size <=0) return -1;
    if(heap->size ==1) return heap->arr[--heap->size];
    int root = heap->arr[0]; heap->arr[0] = heap->arr[--heap->size]; heapify(heap,0); return root;
}

void displayHeap(MaxHeap* heap) {
    for(int i =0; i < heap->size; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

void freeHeap(MaxHeap* heap) { free(heap->arr); free(heap); }

int main() {
    MaxHeap* heap = createMaxHeap(10);
    insertHeap(heap, 10); insertHeap(heap, 20); insertHeap(heap, 15); insertHeap(heap, 30); insertHeap(heap, 40);
    displayHeap(heap);
    printf("Extracted max: %d\n", extractMax(heap));
    displayHeap(heap);
    insertHeap(heap, 50);
    displayHeap(heap);
    while(heap->size >0) { printf("Extracted max: %d\n", extractMax(heap)); displayHeap(heap); }
    freeHeap(heap);
    return 0;
}