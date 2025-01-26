#include <stdio.h>
#include <stdlib.h>

int**** create4DArray(int w, int x, int y, int z) {
    int**** arr = (int****)malloc(w * sizeof(int***));
    for(int i =0; i < w; i++) {
        arr[i] = (int***)malloc(x * sizeof(int**));
        for(int j =0; j < x; j++) {
            arr[i][j] = (int**)malloc(y * sizeof(int*));
            for(int k =0; k < y; k++)
                arr[i][j][k] = (int*)malloc(z * sizeof(int));
        }
    }
    return arr;
}

void free4DArray(int**** arr, int w, int x, int y) {
    for(int i =0; i < w; i++)
        for(int j =0; j < x; j++)
            for(int k =0; k < y; k++)
                free(arr[i][j][k]);
    for(int i =0; i < w; i++)
        for(int j =0; j < x; j++)
            free(arr[i][j]);
    for(int i =0; i < w; i++)
        free(arr[i]);
    free(arr);
}

int main() {
    int w =2, x =2, y=2, z=2;
    int**** array4D = create4DArray(w, x, y, z);
    for(int i =0; i < w; i++)
        for(int j =0; j < x; j++)
            for(int k =0; k < y; k++)
                for(int l =0; l < z; l++)
                    array4D[i][j][k][l] = i*1000 + j*100 + k*10 + l;
    for(int i =0; i < w; i++) {
        printf("W%d:\n", i);
        for(int j =0; j < x; j++) {
            for(int k =0; k < y; k++) printf("%d ", array4D[i][j][k][0]);
            printf("\n");
        }
    }
    free4DArray(array4D, w, x, y);
    return 0;
}