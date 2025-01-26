#include <stdio.h>
#include <stdlib.h>

typedef struct SNode {
    int data;
    struct SNode* next;
} SNode;

SNode* createNode(int data) {
    SNode* newNode = (SNode*)malloc(sizeof(SNode));
    newNode->data = data; newNode->next = NULL;
    return newNode;
}

SNode* insertAtEndS(SNode* head, int data) {
    SNode* newNode = createNode(data);
    if(head == NULL) return newNode;
    SNode* temp = head;
    while(temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return head;
}

void displaySList(SNode* head) {
    while(head != NULL) { printf("%d -> ", head->data); head = head->next; }
    printf("NULL\n");
}

void freeSList(SNode* head) {
    while(head != NULL) { SNode* temp = head; head = head->next; free(temp); }
}

int main() {
    SNode* headS = NULL;
    headS = insertAtEndS(headS, 10); headS = insertAtEndS(headS, 20); headS = insertAtEndS(headS, 5);
    displaySList(headS);
    freeSList(headS);
    return 0;
}