#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node** children;
    int childCount;
} Node;

Node* createNode(int data, int childCount) {
    Node* node = (Node*)malloc(sizeof(Node)); node->data = data; node->childCount = childCount;
    node->children = childCount ? (Node**)malloc(childCount * sizeof(Node*)) : NULL;
    for(int i=0; i<childCount; i++) node->children[i] = NULL;
    return node;
}

void insertChild(Node* parent, int index, Node* child) { if(parent && index < parent->childCount) parent->children[index] = child; }

void inorderGeneric(Node* root) {
    if(!root) return; printf("%d ", root->data);
    for(int i=0; i < root->childCount; i++) inorderGeneric(root->children[i]);
}

int main(){
    Node* root = createNode(1, 3);
    Node* child1 = createNode(2, 2); Node* child2 = createNode(3, 0); Node* child3 = createNode(4, 1);
    insertChild(root, 0, child1); insertChild(root, 1, child2); insertChild(root, 2, child3);
    insertChild(child1, 0, createNode(5, 0)); insertChild(child1, 1, createNode(6, 0));
    insertChild(child3, 0, createNode(7, 0));
    inorderGeneric(root); printf("\n");
    // Free memory omitted
    return 0;
}