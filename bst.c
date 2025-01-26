#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if(!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insertBST(TreeNode* root, int value) {
    if(root == NULL) {
        root = createNode(value);
        printf("Inserted %d into BST.\n", value);
    }
    else if(value < root->data) {
        root->left = insertBST(root->left, value);
    }
    else if(value > root->data) {
        root->right = insertBST(root->right, value);
    }
    else {
        printf("Value %d already exists in BST. Skipping insertion.\n", value);
    }
    return root;
}

TreeNode* searchBST(TreeNode* root, int key) {
    if(root == NULL || root->data == key)
        return root;
    if(key < root->data)
        return searchBST(root->left, key);
    else
        return searchBST(root->right, key);
}

TreeNode* findMin(TreeNode* root) {
    while(root->left != NULL)
        root = root->left;
    return root;
}

TreeNode* deleteBST(TreeNode* root, int key) {
    if(root == NULL) {
        printf("Value %d not found in BST.\n", key);
        return root;
    }
    if(key < root->data)
        root->left = deleteBST(root->left, key);
    else if(key > root->data)
        root->right = deleteBST(root->right, key);
    else {
        if(root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            printf("Deleted %d from BST.\n", key);
            return temp;
        }
        else if(root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            printf("Deleted %d from BST.\n", key);
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteBST(root->right, temp->data);
    }
    return root;
}

void inorderTraversal(TreeNode* root) {
    if(root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
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
    inorderTraversal(root);
    printf("\n");

    int key = 40;
    TreeNode* found = searchBST(root, key);
    if(found != NULL)
        printf("Value %d found in BST.\n", key);
    else
        printf("Value %d not found in BST.\n", key);

    root = deleteBST(root, 20);
    inorderTraversal(root);
    printf("\n");

    root = deleteBST(root, 30);
    inorderTraversal(root);
    printf("\n");

    root = deleteBST(root, 50);
    inorderTraversal(root);
    printf("\n");

    root = deleteBST(root, 100);
    inorderTraversal(root);
    printf("\n");

    freeBST(root);
    return 0;
}
