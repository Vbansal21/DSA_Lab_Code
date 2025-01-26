#include <stdio.h>

int maxSumSubarray(int* arr, int n, int K) {
    if(n < K)
        return -1;
    int window_sum = 0;
    for(int i =0; i < K; i++)
        window_sum += arr[i];
    int max_sum = window_sum;
    for(int i = K; i < n; i++) {
        window_sum += arr[i] - arr[i-K];
        if(window_sum > max_sum)
            max_sum = window_sum;
    }
    return max_sum;
}

int main() {
    int arr[] = {1, 8, 30, -5, 20, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    int K =3;
    int max_sum = maxSumSubarray(arr, n, K);
    if(max_sum != -1)
        printf("Max sum: %d\n", max_sum);
    return 0;
}