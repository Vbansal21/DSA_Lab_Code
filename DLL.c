#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

DNode* createDNode(int data) {
    DNode* newNode = (DNode*)malloc(sizeof(DNode));
    newNode->data = data; newNode->prev = newNode->next = NULL;
    return newNode;
}

DNode* insertAtEndD(DNode* head, int data) {
    DNode* newNode = createDNode(data);
    if(head == NULL) return newNode;
    DNode* temp = head;
    while(temp->next != NULL) temp = temp->next;
    temp->next = newNode; newNode->prev = temp;
    return head;
}

void displayDListForward(DNode* head) {
    while(head != NULL) { printf("%d <-> ", head->data); head = head->next; }
    printf("NULL\n");
}

void displayDListBackward(DNode* head) {
    if(head == NULL) return;
    while(head->next != NULL) head = head->next;
    while(head != NULL) { printf("%d <-> ", head->data); head = head->prev; }
    printf("NULL\n");
}

void freeDList(DNode* head) {
    while(head != NULL) { DNode* temp = head; head = head->next; free(temp); }
}

int main() {
    DNode* headD = NULL;
    headD = insertAtEndD(headD, 10); headD = insertAtEndD(headD, 20); headD = insertAtEndD(headD, 5);
    displayDListForward(headD); displayDListBackward(headD);
    freeDList(headD);
    return 0;
}