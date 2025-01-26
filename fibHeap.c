#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct FibNode {
    int key;
    int degree;
    struct FibNode* parent;
    struct FibNode* child;
    struct FibNode* left;
    struct FibNode* right;
    int mark;
} FibNode;

typedef struct FibHeap {
    FibNode* min;
    int n;
} FibHeap;

FibNode* createFibNode(int key) {
    FibNode* node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key; node->degree =0; node->parent = node->child = NULL; node->left = node->right = node; node->mark =0;
    return node;
}

FibHeap* createFibHeap() {
    FibHeap* heap = (FibHeap*)malloc(sizeof(FibHeap));
    heap->min = NULL; heap->n =0;
    return heap;
}

void swap(int* x, int* y) { int temp = *x; *x = *y; *y = temp; }

void fibHeapLink(FibHeap* heap, FibNode* y, FibNode* x) {
    y->left->right = y->right; y->right->left = y->left;
    y->parent = x;
    if(x->child == NULL) { x->child = y; y->left = y->right = y; }
    else { y->left = x->child; y->right = x->child->right; x->child->right->left = y; x->child->right = y; }
    x->degree++; y->mark =0;
}

void fibHeapConsolidate(FibHeap* heap) {
    int D = floor(log2(heap->n)) +1;
    FibNode** A = (FibNode**)calloc(D, sizeof(FibNode*));
    FibNode* start = heap->min; if(start == NULL) return;
    FibNode* current = start;
    do {
        FibNode* x = current; int d = x->degree;
        while(A[d] != NULL) {
            FibNode* y = A[d]; if(x->key > y->key) { FibNode* temp = x; x = y; y = temp; }
            fibHeapLink(heap, y, x); A[d] = NULL; d++;
        }
        A[d] = x; current = current->right;
    } while(current != start);
    heap->min = NULL;
    for(int i =0; i < D; i++) {
        if(A[i] != NULL) {
            if(heap->min == NULL) { heap->min = A[i]; heap->min->left = heap->min->right = heap->min; }
            else {
                A[i]->left = heap->min; A[i]->right = heap->min->right; heap->min->right->left = A[i]; heap->min->right = A[i];
                if(A[i]->key < heap->min->key) heap->min = A[i];
            }
        }
    }
    free(A);
}

void fibHeapInsert(FibHeap* heap, FibNode* node) {
    if(heap->min == NULL) heap->min = node;
    else { node->left = heap->min; node->right = heap->min->right; heap->min->right->left = node; heap->min->right = node; if(node->key < heap->min->key) heap->min = node; }
    heap->n++;
}

FibNode* fibHeapExtractMin(FibHeap* heap) {
    FibNode* z = heap->min; if(z == NULL) return NULL;
    if(z->child != NULL) {
        FibNode* child = z->child;
        do {
            FibNode* next = child->right;
            child->left->right = child->right; child->right->left = child->left;
            child->left = heap->min; child->right = heap->min->right; heap->min->right->left = child; heap->min->right = child;
            child->parent = NULL; child = next;
        } while(child != z->child);
    }
    z->left->right = z->right; z->right->left = z->left;
    if(z == z->right) heap->min = NULL;
    else { heap->min = z->right; fibHeapConsolidate(heap); }
    heap->n--; return z;
}

void freeFibHeap(FibNode* node) {
    if(node == NULL) return;
    FibNode* start = node; FibNode* current = node->right;
    while(current != start) { freeFibHeap(current->child); FibNode* temp = current; current = current->right; free(temp); }
    freeFibHeap(node->child); free(node);
}

int main() {
    FibHeap* heap = createFibHeap();
    fibHeapInsert(heap, createFibNode(10));
    fibHeapInsert(heap, createFibNode(3));
    fibHeapInsert(heap, createFibNode(15));
    fibHeapInsert(heap, createFibNode(6));
    fibHeapInsert(heap, createFibNode(8));
    FibNode* minNode = heap->min; if(minNode != NULL) printf("Min: %d\n", minNode->key);
    FibNode* extracted = fibHeapExtractMin(heap); if(extracted != NULL) printf("Extracted: %d\n", extracted->key);
    minNode = heap->min; if(minNode != NULL) printf("New Min: %d\n", minNode->key);
    fibHeapInsert(heap, createFibNode(1));
    extracted = fibHeapExtractMin(heap); if(extracted != NULL) printf("Extracted: %d\n", extracted->key);
    freeFibHeap(heap->min); free(heap);
    return 0;
}