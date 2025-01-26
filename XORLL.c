#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct XORNode {
    int data;
    struct XORNode* npx;
} XORNode;

XORNode* createNode(int data) { XORNode* node = (XORNode*)malloc(sizeof(XORNode)); node->data = data; node->npx = NULL; return node; }

XORNode* XOR(XORNode* a, XORNode* b) { return (XORNode*)((uintptr_t)(a) ^ (uintptr_t)(b)); }

void insertEnd(XORNode** head, int data) {
    XORNode* newNode = createNode(data);
    if(!(*head)) { *head = newNode; return; }
    XORNode* current = *head; XORNode* prev = NULL; XORNode* next;
    while(current->npx) { next = XOR(prev, current->npx); prev = current; current = next; }
    current->npx = XOR(prev, newNode); newNode->npx = current;
}

void printList(XORNode* head) {
    XORNode* current = head; XORNode* prev = NULL; XORNode* next;
    while(current) { printf("%d -> ", current->data); next = XOR(prev, current->npx); prev = current; current = next; }
    printf("NULL\n");
}

int main(){
    XORNode* head = NULL; insertEnd(&head, 10); insertEnd(&head, 20); insertEnd(&head, 30);
    printList(head); return 0;
}