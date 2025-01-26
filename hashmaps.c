#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10
#define EMPTY -1
#define DELETED -2

typedef struct Pair {
    int key;
    int value;
} Pair;

typedef struct HashMap {
    Pair* table;
} HashMap;

HashMap* createHashMap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->table = (Pair*)malloc(HASH_SIZE * sizeof(Pair));
    for(int i =0; i < HASH_SIZE; i++) { map->table[i].key = EMPTY; map->table[i].value =0; }
    return map;
}

int hashFunction(int key) { return key % HASH_SIZE; }

void insertHashMapLP(HashMap* map, int key, int value) {
    int index = hashFunction(key); int original = index; int i =1;
    while(map->table[index].key != EMPTY && map->table[index].key != DELETED && map->table[index].key != key)
        { index = (original + i++) % HASH_SIZE; if(index == original) { printf("Full\n"); return; } }
    if(map->table[index].key == key) { map->table[index].value = value; }
    else { map->table[index].key = key; map->table[index].value = value; }
}

int searchHashMapLP(HashMap* map, int key) {
    int index = hashFunction(key); int original = index; int i =1;
    while(map->table[index].key != EMPTY) {
        if(map->table[index].key == key) return map->table[index].value;
        index = (original + i++) % HASH_SIZE; if(index == original) break;
    }
    return -1;
}

void deleteHashMapLP(HashMap* map, int key) {
    int index = hashFunction(key); int original = index; int i =1;
    while(map->table[index].key != EMPTY) {
        if(map->table[index].key == key) { map->table[index].key = DELETED; return; }
        index = (original + i++) % HASH_SIZE; if(index == original) break;
    }
}

void displayHashMapLP(HashMap* map) {
    for(int i =0; i < HASH_SIZE; i++) {
        if(map->table[i].key == EMPTY) printf("Bucket %d: EMPTY\n", i);
        else if(map->table[i].key == DELETED) printf("Bucket %d: DELETED\n", i);
        else printf("Bucket %d: Key = %d, Value = %d\n", i, map->table[i].key, map->table[i].value);
    }
}

void freeHashMapLP(HashMap* map) { free(map->table); free(map); }

int main() {
    HashMap* map = createHashMap();
    insertHashMapLP(map, 1, 100); insertHashMapLP(map, 11, 200); insertHashMapLP(map, 21, 300);
    insertHashMapLP(map, 2, 400); insertHashMapLP(map, 12, 500);
    displayHashMapLP(map);
    printf("Search 21: %d\n", searchHashMapLP(map, 21));
    printf("Search 3: %d\n", searchHashMapLP(map, 3));
    deleteHashMapLP(map, 11); displayHashMapLP(map);
    insertHashMapLP(map, 31, 600); displayHashMapLP(map);
    freeHashMapLP(map);
    return 0;
}