#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for(int i =0; i < ALPHABET_SIZE; i++) node->children[i] = NULL;
    return node;
}

void insert(TrieNode* root, const char* key) {
    TrieNode* p = root;
    for(int i =0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if(index <0 || index >= ALPHABET_SIZE) return;
        if(!p->children[index]) p->children[index] = createNode();
        p = p->children[index];
    }
    p->isEndOfWord = true;
}

bool search(TrieNode* root, const char* key) {
    TrieNode* p = root;
    for(int i =0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if(index <0 || index >= ALPHABET_SIZE || !p->children[index]) return false;
        p = p->children[index];
    }
    return p != NULL && p->isEndOfWord;
}

bool hasChildren(TrieNode* node) {
    for(int i =0; i < ALPHABET_SIZE; i++) if(node->children[i] != NULL) return true;
    return false;
}

bool deleteWord(TrieNode* root, const char* key, int depth) {
    if(root == NULL) return false;
    if(key[depth] == '\0') {
        if(root->isEndOfWord) { root->isEndOfWord = false; return !hasChildren(root); }
    }
    else {
        int index = key[depth] - 'a';
        if(index <0 || index >= ALPHABET_SIZE) return false;
        if(deleteWord(root->children[index], key, depth +1)) {
            free(root->children[index]); root->children[index] = NULL;
            return !hasChildren(root) && !root->isEndOfWord;
        }
    }
    return false;
}

void freeTrie(TrieNode* root) {
    if(root == NULL) return;
    for(int i =0; i < ALPHABET_SIZE; i++) freeTrie(root->children[i]);
    free(root);
}

int main() {
    TrieNode* root = createNode();
    insert(root, "hello"); insert(root, "hell"); insert(root, "heaven"); insert(root, "goodbye");
    printf("hell: %s\n", search(root, "hell") ? "Found" : "Not Found");
    printf("heaven: %s\n", search(root, "heaven") ? "Found" : "Not Found");
    printf("good: %s\n", search(root, "good") ? "Found" : "Not Found");
    if(deleteWord(root, "hell", 0)) printf("Deleted 'hell'\n");
    printf("hell after deletion: %s\n", search(root, "hell") ? "Found" : "Not Found");
    freeTrie(root);
    return 0;
}