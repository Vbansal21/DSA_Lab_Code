#include <stdio.h>

int fibonacci(int n) {
    if(n <0)
        return -1;
    if(n ==0)
        return 0;
    if(n ==1)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int n =10;
    int fib = fibonacci(n);
    if(fib != -1)
        printf("Fibonacci at %d is %d\n", n, fib);
    else
        printf("Undefined.\n");
    return 0;
}