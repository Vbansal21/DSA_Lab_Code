#include <stdio.h>

int maxSubArraySum(int* arr, int n) {
    int max_so_far = arr[0], current_max = arr[0];
    for(int i =1; i < n; i++) {
        current_max = (current_max + arr[i] > arr[i]) ? current_max + arr[i] : arr[i];
        if(current_max > max_so_far)
            max_so_far = current_max;
    }
    return max_so_far;
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr)/sizeof(arr[0]);
    int max_sum = maxSubArraySum(arr, n);
    printf("Max contiguous sum: %d\n", max_sum);
    return 0;
}