#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key, height;
    struct AVLNode *left, *right;
} AVLNode;

int height(AVLNode *N) { return N ? N->height : 0; }
int max(int a, int b) { return (a > b) ? a : b; }

AVLNode* newNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key; node->left = node->right = NULL; node->height = 1;
    return node;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left; AVLNode* T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max(height(y->left), height(y->right)) +1;
    x->height = max(height(x->left), height(x->right)) +1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right; AVLNode* T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max(height(x->left), height(x->right)) +1;
    y->height = max(height(y->left), height(y->right)) +1;
    return y;
}

int getBalance(AVLNode* N) { return N ? height(N->left) - height(N->right) : 0; }

AVLNode* insertAVL(AVLNode* node, int key) {
    if(!node) return newNode(key);
    if(key < node->key) node->left = insertAVL(node->left, key);
    else if(key > node->key) node->right = insertAVL(node->right, key);
    else return node;
    node->height = max(height(node->left), height(node->right)) +1;
    int balance = getBalance(node);
    if(balance >1 && key < node->left->key) return rightRotate(node);
    if(balance < -1 && key > node->right->key) return leftRotate(node);
    if(balance >1 && key > node->left->key) { node->left = leftRotate(node->left); return rightRotate(node); }
    if(balance < -1 && key < node->right->key) { node->right = rightRotate(node->right); return leftRotate(node); }
    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node; while(current->left) current = current->left; return current;
}

AVLNode* deleteAVL(AVLNode* root, int key) {
    if(!root) return root;
    if(key < root->key) root->left = deleteAVL(root->left, key);
    else if(key > root->key) root->right = deleteAVL(root->right, key);
    else { if(!root->left || !root->right) { AVLNode* temp = root->left ? root->left : root->right; if(!temp) { temp = root; root = NULL; } else *root = *temp; free(temp); }
        else { AVLNode* temp = minValueNode(root->right); root->key = temp->key; root->right = deleteAVL(root->right, temp->key); }
    }
    if(!root) return root;
    root->height = max(height(root->left), height(root->right)) +1;
    int balance = getBalance(root);
    if(balance >1 && getBalance(root->left) >=0) return rightRotate(root);
    if(balance >1 && getBalance(root->left) <0) { root->left = leftRotate(root->left); return rightRotate(root); }
    if(balance < -1 && getBalance(root->right) <=0) return leftRotate(root);
    if(balance < -1 && getBalance(root->right) >0) { root->right = rightRotate(root->right); return leftRotate(root); }
    return root;
}

void preOrder(AVLNode* root) { if(root) { printf("%d ", root->key); preOrder(root->left); preOrder(root->right); } }

int main(){
    AVLNode* root = NULL;
    root = insertAVL(root, 10); root = insertAVL(root, 20); root = insertAVL(root, 30);
    root = insertAVL(root, 40); root = insertAVL(root, 50); root = insertAVL(root, 25);
    printf("Preorder traversal: "); preOrder(root); printf("\n");
    root = deleteAVL(root, 40); printf("Preorder after deletion: "); preOrder(root); printf("\n");
    return 0;
}