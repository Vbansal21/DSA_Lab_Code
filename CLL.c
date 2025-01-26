#include <stdio.h>
#include <stdlib.h>

typedef struct CNode {
    int data;
    struct CNode* next;
} CNode;

CNode* createCNode(int data) {
    CNode* newNode = (CNode*)malloc(sizeof(CNode));
    newNode->data = data; newNode->next = newNode;
    return newNode;
}

CNode* insertAtEndC(CNode* head, int data) {
    CNode* newNode = createCNode(data);
    if(head == NULL) return newNode;
    CNode* temp = head;
    while(temp->next != head) temp = temp->next;
    temp->next = newNode; newNode->next = head;
    return head;
}

void displayCList(CNode* head) {
    if(head == NULL) { printf("Empty\n"); return; }
    CNode* temp = head;
    do { printf("%d -> ", temp->data); temp = temp->next; } while(temp != head);
    printf("(back to head)\n");
}

void freeCList(CNode* head) {
    if(head == NULL) return;
    CNode* temp = head->next;
    while(temp != head) { CNode* toFree = temp; temp = temp->next; free(toFree); }
    free(head);
}

int main() {
    CNode* headC = NULL;
    headC = insertAtEndC(headC, 10); headC = insertAtEndC(headC, 20); headC = insertAtEndC(headC, 30);
    displayCList(headC);
    freeCList(headC);
    return 0;
}