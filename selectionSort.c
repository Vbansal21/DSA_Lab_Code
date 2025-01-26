#include <stdio.h>

void selectionSort(int* arr, int n) {
    for(int i =0; i < n-1; i++) {
        int min_idx = i;
        for(int j =i+1; j < n; j++)
            if(arr[j] < arr[min_idx])
                min_idx = j;
        if(min_idx != i) { int temp = arr[min_idx]; arr[min_idx] = arr[i]; arr[i] = temp; }
    }
}

void display(int* arr, int n) {
    for(int i =0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {29, 10, 14, 37, 13};
    int n = sizeof(arr)/sizeof(arr[0]);
    display(arr, n);
    selectionSort(arr, n);
    display(arr, n);
    return 0;
}