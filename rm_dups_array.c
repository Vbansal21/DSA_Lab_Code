#include <stdio.h>

int removeDuplicates(int* arr, int n) {
    if (n == 0 || n == 1)
        return n;
    int j = 0;
    for (int i = 0; i < n-1; i++)
        if (arr[i] != arr[i+1])
            arr[j++] = arr[i];
    arr[j++] = arr[n-1];
    return j;
}

int main() {
    int arr[] = {10, 20, 20, 30, 40, 40, 40, 50};
    int n = sizeof(arr)/sizeof(arr[0]);
    int newLength = removeDuplicates(arr, n);
    for(int i = 0; i < newLength; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}