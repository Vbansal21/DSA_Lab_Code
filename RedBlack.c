#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode* createNode(int key) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key; node->color = RED; node->left = node->right = node->parent = NULL;
    return node;
}

void rotateLeft(RBNode** root, RBNode* x) {
    RBNode* y = x->right; x->right = y->left;
    if(y->left) y->left->parent = x;
    y->parent = x->parent;
    if(!x->parent) *root = y;
    else if(x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; x->parent = y;
}

void rotateRight(RBNode** root, RBNode* y) {
    RBNode* x = y->left; y->left = x->right;
    if(x->right) x->right->parent = y;
    x->parent = y->parent;
    if(!y->parent) *root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y; y->parent = x;
}

void fixViolation(RBNode** root, RBNode* z) {
    while(z->parent && z->parent->color == RED) {
        if(z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if(y && y->color == RED) { z->parent->color = BLACK; y->color = BLACK; z->parent->parent->color = RED; z = z->parent->parent; }
            else {
                if(z == z->parent->right) { z = z->parent; rotateLeft(root, z); }
                z->parent->color = BLACK; z->parent->parent->color = RED; rotateRight(root, z->parent->parent);
            }
        }
        else {
            RBNode* y = z->parent->parent->left;
            if(y && y->color == RED) { z->parent->color = BLACK; y->color = BLACK; z->parent->parent->color = RED; z = z->parent->parent; }
            else {
                if(z == z->parent->left) { z = z->parent; rotateRight(root, z); }
                z->parent->color = BLACK; z->parent->parent->color = RED; rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void insertRB(RBNode** root, int key) {
    RBNode* z = createNode(key); RBNode* y = NULL; RBNode* x = *root;
    while(x) { y = x; if(z->key < x->key) x = x->left; else if(z->key > x->key) x = x->right; else { free(z); return; } }
    z->parent = y;
    if(!y) { *root = z; }
    else if(z->key < y->key) y->left = z;
    else y->right = z;
    fixViolation(root, z);
}

void inorderRB(RBNode* root) {
    if(root) { inorderRB(root->left); printf("%d(%s) ", root->key, root->color == RED ? "R" : "B"); inorderRB(root->right); }
}

int main(){
    RBNode* root = NULL;
    int keys[] = {10, 20, 30, 15, 25, 5, 1};
    for(int i=0; i < sizeof(keys)/sizeof(keys[0]); i++) insertRB(&root, keys[i]);
    inorderRB(root); printf("\n");
    return 0;
}