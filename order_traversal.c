#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insertBST(TreeNode* root, int data) {
    if(root == NULL)
        return createNode(data);
    if(data < root->data)
        root->left = insertBST(root->left, data);
    else if(data > root->data)
        root->right = insertBST(root->right, data);
    return root;
}

void preorderTraversal(TreeNode* root) {
    if(root == NULL)
        return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(TreeNode* root) {
    if(root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

void postorderTraversal(TreeNode* root) {
    if(root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

void freeBST(TreeNode* root) {
    if(root == NULL)
        return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

int main() {
    TreeNode* root = NULL;
    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 70);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    root = insertBST(root, 60);
    root = insertBST(root, 80);
    printf("Pre-order traversal: ");
    preorderTraversal(root);
    printf("\nIn-order traversal: ");
    inorderTraversal(root);
    printf("\nPost-order traversal: ");
    postorderTraversal(root);
    printf("\n");
    freeBST(root);
    return 0;
}