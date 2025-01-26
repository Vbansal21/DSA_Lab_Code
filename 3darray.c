#include <stdio.h>
#include <stdlib.h>

int*** create3DArray(int x, int y, int z) {
    int*** array = (int***)malloc(x * sizeof(int**));
    for(int i = 0; i < x; i++) {
        array[i] = (int**)malloc(y * sizeof(int*));
        for(int j = 0; j < y; j++)
            array[i][j] = (int*)malloc(z * sizeof(int));
    }
    return array;
}

void free3DArray(int*** array, int x, int y) {
    for(int i =0; i < x; i++)
        for(int j =0; j < y; j++)
            free(array[i][j]);
    for(int i =0; i < x; i++)
        free(array[i]);
    free(array);
}

int main() {
    int x =2, y =3, z =4;
    int*** array = create3DArray(x, y, z);
    for(int i =0; i < x; i++)
        for(int j =0; j < y; j++)
            for(int k =0; k < z; k++)
                array[i][j][k] = i*100 + j*10 + k;
    for(int i =0; i < x; i++) {
        printf("Layer %d:\n", i);
        for(int j =0; j < y; j++) {
            for(int k =0; k < z; k++)
                printf("%d ", array[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
    free3DArray(array, x, y);
    return 0;
}