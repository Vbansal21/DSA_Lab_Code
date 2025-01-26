#include <stdio.h>
#include <stdlib.h>

typedef struct SplayNode {
    int key;
    struct SplayNode *left, *right, *parent;
} SplayNode;

SplayNode* createNode(int key) {
    SplayNode* node = (SplayNode*)malloc(sizeof(SplayNode));
    node->key = key; node->left = node->right = node->parent = NULL;
    return node;
}

void rotateLeft(SplayNode** root, SplayNode* x) {
    SplayNode* y = x->right; x->right = y->left;
    if(y->left) y->left->parent = x;
    y->parent = x->parent;
    if(!x->parent) *root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; x->parent = y;
}

void rotateRight(SplayNode** root, SplayNode* y) {
    SplayNode* x = y->left; y->left = x->right;
    if(x->right) x->right->parent = y;
    x->parent = y->parent;
    if(!y->parent) *root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y; y->parent = x;
}

void splay(SplayNode** root, SplayNode* x) {
    while(x->parent) {
        if(!x->parent->parent) {
            if(x->parent->left == x) rotateRight(root, x->parent);
            else rotateLeft(root, x->parent);
        }
        else if(x->parent->left == x && x->parent->parent->left == x->parent) {
            rotateRight(root, x->parent->parent); rotateRight(root, x->parent);
        }
        else if(x->parent->right == x && x->parent->parent->right == x->parent) {
            rotateLeft(root, x->parent->parent); rotateLeft(root, x->parent);
        }
        else if(x->parent->left == x && x->parent->parent->right == x->parent) {
            rotateRight(root, x->parent); rotateLeft(root, x->parent);
        }
        else {
            rotateLeft(root, x->parent); rotateRight(root, x->parent);
        }
    }
    *root = x;
}

SplayNode* search(SplayNode** root, int key) {
    SplayNode* x = *root;
    while(x) {
        if(key == x->key) { splay(root, x); return x; }
        if(key < x->key) x = x->left;
        else x = x->right;
    }
    return NULL;
}

SplayNode* insert(SplayNode** root, int key) {
    SplayNode* z = *root; SplayNode* p = NULL;
    while(z) { p = z; if(key < z->key) z = z->left; else if(key > z->key) z = z->right; else { splay(root, z); return z; } }
    z = createNode(key); z->parent = p;
    if(!p) { *root = z; }
    else if(key < p->key) p->left = z;
    else p->right = z;
    splay(root, z);
    return z;
}

SplayNode* maximum(SplayNode* root) {
    while(root->right) root = root->right; return root;
}

SplayNode* deleteNode(SplayNode** root, int key) {
    SplayNode* node = search(root, key);
    if(!node) return NULL;
    if(!node->left) { *root = node->right; if(*root) (*root)->parent = NULL; }
    else {
        SplayNode* y = maximum(node->left);
        splay(root, y);
        y->right = node->right; if(y->right) y->right->parent = y;
    }
    free(node); return *root;
}

void inorder(SplayNode* root) {
    if(root) { inorder(root->left); printf("%d ", root->key); inorder(root->right); }
}

int main(){
    SplayNode* root = NULL;
    insert(&root, 10); insert(&root, 20); insert(&root, 30);
    insert(&root, 40); insert(&root, 50); insert(&root, 25);
    printf("Inorder: "); inorder(root); printf("\n");
    deleteNode(&root, 40); printf("Inorder after deletion: "); inorder(root); printf("\n");
    return 0;
}