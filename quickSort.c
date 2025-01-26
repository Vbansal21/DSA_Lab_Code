#include <stdio.h>

void swap(int* a, int* b) { int temp = *a; *a = *b; *b = temp; }

int partition(int* arr, int low, int high) {
    int pivot = arr[high], i = low -1;
    for(int j = low; j <= high-1; j++) if(arr[j] <= pivot) { swap(&arr[i+1], &arr[j]); i++; }
    swap(&arr[i+1], &arr[high]); return i+1;
}

void quickSort(int* arr, int low, int high) {
    if(low < high) { int pi = partition(arr, low, high); quickSort(arr, low, pi-1); quickSort(arr, pi+1, high); }
}

void display(int* arr, int n) {
    for(int i =0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    display(arr, n);
    quickSort(arr, 0, n-1);
    display(arr, n);
    return 0;
}