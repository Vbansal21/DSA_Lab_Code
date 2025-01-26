#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct HashNode {
    int key;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode** buckets;
} HashTable;

HashNode* createNode(int key) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (HashNode**)malloc(TABLE_SIZE * sizeof(HashNode*));
    for(int i = 0; i < TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    return table;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insertHash(HashTable* table, int key) {
    int index = hashFunction(key);
    HashNode* newNode = createNode(key);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    printf("Inserted key %d at index %d\n", key, index);
}

int searchHash(HashTable* table, int key) {
    int index = hashFunction(key);
    HashNode* temp = table->buckets[index];
    while (temp != NULL) {
        if (temp->key == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void deleteHash(HashTable* table, int key) {
    int index = hashFunction(key);
    HashNode* temp = table->buckets[index];
    HashNode* prev = NULL;
    while (temp != NULL && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Key %d not found.\n", key);
        return;
    }
    if (prev == NULL)
        table->buckets[index] = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    printf("Deleted key %d from index %d\n", key, index);
}

void displayHashTable(HashTable* table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        HashNode* temp = table->buckets[i];
        while(temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freeHashTable(HashTable* table) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        HashNode* temp = table->buckets[i];
        while(temp != NULL) {
            HashNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(table->buckets);
    free(table);
}

int main() {
    HashTable* table = createHashTable();
    insertHash(table, 15);
    insertHash(table, 25);
    insertHash(table, 35);
    insertHash(table, 20);
    insertHash(table, 10);
    insertHash(table, 30);
    displayHashTable(table);
    int keysToSearch[] = {25, 40};
    for(int i = 0; i < 2; i++) {
        int found = searchHash(table, keysToSearch[i]);
        printf("Search for key %d: %s\n", keysToSearch[i], found ? "Found" : "Not Found");
    }
    deleteHash(table, 25);
    displayHashTable(table);
    deleteHash(table, 100);
    freeHashTable(table);
    return 0;
}