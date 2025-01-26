#include <stdio.h>
#include <stdlib.h>

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

#define HASH_SIZE 1000

HashNode* createHashNode(int key, int value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

int hashFunction(int key) {
    return abs(key) % HASH_SIZE;
}

void insertHashTable(HashNode** hashTable, int key, int value) {
    int index = hashFunction(key);
    HashNode* node = createHashNode(key, value);
    node->next = hashTable[index];
    hashTable[index] = node;
}

int searchHashTable(HashNode** hashTable, int key) {
    int index = hashFunction(key);
    HashNode* temp = hashTable[index];
    while(temp != NULL) {
        if(temp->key == key)
            return temp->value;
        temp = temp->next;
    }
    return -1;
}

void twoSumOptimized(int* arr, int n, int target) {
    HashNode** hashTable = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));
    for(int i =0; i < n; i++) {
        int complement = target - arr[i];
        int index = searchHashTable(hashTable, complement);
        if(index != -1) {
            printf("Indices %d and %d\n", index, i);
            break;
        }
        insertHashTable(hashTable, arr[i], i);
    }
    for(int i =0; i < HASH_SIZE; i++) {
        HashNode* temp = hashTable[i];
        while(temp != NULL) {
            HashNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(hashTable);
}

int main() {
    int arr[] = {2, 7, 11, 15};
    int n = sizeof(arr)/sizeof(arr[0]);
    twoSumOptimized(arr, n, 9);
    return 0;
}