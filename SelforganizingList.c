#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) { Node* node = (Node*)malloc(sizeof(Node)); node->data = data; node->next = NULL; return node; }

void insertEnd(Node** head, int data) { Node* newNode = createNode(data); if(!(*head)) { *head = newNode; return; } Node* temp = *head; while(temp->next) temp = temp->next; temp->next = newNode; }

Node* searchList(Node** head, int key) {
    Node* current = *head; Node* prev = NULL;
    while(current && current->data != key) { prev = current; current = current->next; }
    if(!current) return NULL;
    if(prev) { prev->next = current->next; current->next = *head; *head = current; }
    return current;
}

void displayList(Node* head) {
    while(head) { printf("%d -> ", head->data); head = head->next; }
    printf("NULL\n");
}

int main(){
    Node* head = NULL; insertEnd(&head, 10); insertEnd(&head, 20); insertEnd(&head, 30); insertEnd(&head, 20);
    displayList(head); searchList(&head, 20); displayList(head);
    return 0;
}