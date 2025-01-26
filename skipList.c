#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 6

typedef struct SkipNode {
    int key;
    struct SkipNode** forward;
} SkipNode;

typedef struct SkipList {
    int level;
    SkipNode* header;
} SkipList;

SkipNode* createNode(int key, int level) {
    SkipNode* node = (SkipNode*)malloc(sizeof(SkipNode));
    node->key = key; node->forward = (SkipNode**)malloc((level +1) * sizeof(SkipNode*));
    for(int i =0; i <= level; i++) node->forward[i] = NULL;
    return node;
}

SkipList* createSkipList() {
    SkipList* list = (SkipList*)malloc(sizeof(SkipList));
    list->level =0; list->header = createNode(-1, MAX_LEVEL);
    for(int i =0; i <= MAX_LEVEL; i++) list->header->forward[i] = NULL;
    return list;
}

int randomLevel() {
    int level =0; while(rand() < RAND_MAX/2 && level < MAX_LEVEL) level++;
    return level;
}

void fibHeapLink(SkipList* list, SkipNode* y, SkipNode* x) { y->forward[0] = x->forward[0]; x->forward[0] = y; }

void insertSkipList(SkipList* list, int key) {
    SkipNode* current = list->header; SkipNode* update[MAX_LEVEL +1];
    for(int i = list->level; i >=0; i--) { while(current->forward[i] != NULL && current->forward[i]->key < key) current = current->forward[i]; update[i] = current; }
    current = current->forward[0];
    if(current == NULL || current->key != key) {
        int rlevel = randomLevel();
        if(rlevel > list->level) { for(int i = list->level +1; i <= rlevel; i++) update[i] = list->header; list->level = rlevel; }
        SkipNode* newNode = createNode(key, rlevel);
        for(int i =0; i <= rlevel; i++) { newNode->forward[i] = update[i]->forward[i]; update[i]->forward[i] = newNode; }
    }
}

int searchSkipList(SkipList* list, int key) {
    SkipNode* current = list->header;
    for(int i = list->level; i >=0; i--)
        while(current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
    current = current->forward[0];
    if(current != NULL && current->key == key) return 1;
    return 0;
}

void displaySkipList(SkipList* list) {
    for(int i =0; i <= list->level; i++) {
        SkipNode* node = list->header->forward[i];
        printf("Level %d: ", i);
        while(node != NULL) { printf("%d ", node->key); node = node->forward[i]; }
        printf("\n");
    }
}

void freeSkipList(SkipList* list) {
    SkipNode* current = list->header->forward[0];
    while(current != NULL) { free(current->forward); SkipNode* temp = current; current = current->forward[0]; free(temp); }
    free(list->header->forward); free(list->header); free(list);
}

int main() {
    srand(time(NULL)); SkipList* list = createSkipList();
    int keys[] = {3,6,7,9,12,19,17,26,21,25};
    for(int i =0; i <10; i++) insertSkipList(list, keys[i]);
    displaySkipList(list);
    int searchKeys[] = {19,15};
    for(int i =0; i <2; i++) printf("Search %d: %s\n", searchKeys[i], searchSkipList(list, searchKeys[i]) ? "Found" : "Not Found");
    freeSkipList(list);
    return 0;
}