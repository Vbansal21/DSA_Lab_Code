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
    if(!node) {
        printf("Memory allocation error\n");
        exit(1);
    }
    node->isEndOfWord = false;
    for(int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode* root, const char* key) {
    TrieNode* pCrawl = root;

    for(int level = 0; key[level] != '\0'; level++) {
        int index = key[level] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE) {
            printf("Invalid character '%c' in word '%s'. Skipping.\n", key[level], key);
            return;
        }
        if(!pCrawl->children[index])
            pCrawl->children[index] = createNode();
        pCrawl = pCrawl->children[index];
    }

    pCrawl->isEndOfWord = true;
    printf("Inserted word '%s' into Trie.\n", key);
}

bool search(TrieNode* root, const char* key) {
    TrieNode* pCrawl = root;

    for(int level = 0; key[level] != '\0'; level++) {
        int index = key[level] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE)
            return false;
        if(!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

bool startsWith(TrieNode* root, const char* prefix) {
    TrieNode* pCrawl = root;

    for(int level = 0; prefix[level] != '\0'; level++) {
        int index = prefix[level] - 'a';
        if(index < 0 || index >= ALPHABET_SIZE)
            return false;
        if(!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }

    return true;
}

void freeTrie(TrieNode* root) {
    if(root == NULL)
        return;
    for(int i = 0; i < ALPHABET_SIZE; i++)
        freeTrie(root->children[i]);
    free(root);
}

int main() {
    TrieNode* root = createNode();

    char* words[] = {"hello", "hell", "heaven", "goodbye"};
    int n = sizeof(words)/sizeof(words[0]);

    for(int i = 0; i < n; i++)
        insert(root, words[i]);

    char* searchWords[] = {"hell", "hello", "heaven", "good", "goo"};
    int m = sizeof(searchWords)/sizeof(searchWords[0]);

    for(int i = 0; i < m; i++) {
        printf("Search for '%s': %s\n", searchWords[i],
               search(root, searchWords[i]) ? "Found" : "Not Found");
    }

    char* prefixes[] = {"he", "goo", "bad"};
    int p = sizeof(prefixes)/sizeof(prefixes[0]);

    for(int i = 0; i < p; i++) {
        printf("Prefix '%s' exists: %s\n", prefixes[i],
               startsWith(root, prefixes[i]) ? "Yes" : "No");
    }

    freeTrie(root);
    return 0;
}