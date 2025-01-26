#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode* children[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf; node->n = 0;
    for(int i=0; i < 2*T; i++) node->children[i] = NULL;
    return node;
}

void traverse(BTreeNode* root) {
    if(root) {
        int i;
        for(i=0; i < root->n; i++) {
            if(!root->leaf) traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        if(!root->leaf) traverse(root->children[i]);
    }
}

BTreeNode* searchBT(BTreeNode* root, int key) {
    int i=0;
    while(i < root->n && key > root->keys[i]) i++;
    if(i < root->n && root->keys[i] == key) return root;
    if(root->leaf) return NULL;
    return searchBT(root->children[i], key);
}

void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* z = createNode(child->leaf);
    z->n = T-1;
    for(int j=0; j < T-1; j++) z->keys[j] = child->keys[j+T];
    if(!child->leaf) {
        for(int j=0; j < T; j++) z->children[j] = child->children[j+T];
    }
    child->n = T-1;
    for(int j=parent->n; j >= i+1; j--) parent->children[j+1] = parent->children[j];
    parent->children[i+1] = z;
    for(int j=parent->n-1; j >=i; j--) parent->keys[j+1] = parent->keys[j];
    parent->keys[i] = child->keys[T-1];
    parent->n +=1;
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->n-1;
    if(node->leaf) {
        while(i >=0 && node->keys[i] > key) { node->keys[i+1] = node->keys[i]; i--; }
        node->keys[i+1] = key; node->n +=1;
    }
    else {
        while(i >=0 && node->keys[i] > key) i--;
        i++;
        if(node->children[i]->n == 2*T-1) {
            splitChild(node, i, node->children[i]);
            if(node->keys[i] < key) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void insertBT(BTreeNode** root, int key) {
    if(*root == NULL) { *root = createNode(1); (*root)->keys[0] = key; (*root)->n =1; }
    else {
        if((*root)->n == 2*T-1) {
            BTreeNode* s = createNode(0); s->children[0] = *root; splitChild(s, 0, *root);
            int i=0; if(s->keys[0] < key) i++;
            insertNonFull(s->children[i], key); *root = s;
        }
        else insertNonFull(*root, key);
    }
}

int main(){
    BTreeNode* root = NULL;
    int keys[] = {10,20,5,6,12,30,7,17};
    for(int i=0; i < sizeof(keys)/sizeof(keys[0]); i++) insertBT(&root, keys[i]);
    traverse(root); printf("\n");
    printf("Search 6: %s\n", searchBT(root, 6) ? "Found" : "Not Found");
    printf("Search 15: %s\n", searchBT(root, 15) ? "Found" : "Not Found");
    return 0;
}