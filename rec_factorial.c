#include <stdio.h>

long long factorial(int n) {
    if(n < 0)
        return -1;
    if(n ==0 || n ==1)
        return 1;
    else
        return n * factorial(n-1);
}

int main() {
    int num =5;
    long long fact = factorial(num);
    if(fact != -1)
        printf("Factorial of %d is %lld\n", num, fact);
    else
        printf("Undefined.\n");
    return 0;
}