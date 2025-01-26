#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data; newNode->prev = newNode->next = NULL;
    return newNode;
}

Node* insertEndD(Node* head, int data) {
    Node* newNode = createNode(data);
    if(head == NULL) return newNode;
    Node* temp = head;
    while(temp->next != NULL) temp = temp->next;
    temp->next = newNode; newNode->prev = temp;
    return head;
}

void displayDListForward(Node* head) {
    while(head != NULL) { printf("%d <-> ", head->data); head = head->next; }
    printf("NULL\n");
}

void displayDListBackward(Node* head) {
    if(head == NULL) return;
    while(head->next != NULL) head = head->next;
    while(head != NULL) { printf("%d <-> ", head->data); head = head->prev; }
    printf("NULL\n");
}

void reverseList(Node** head_ref) {
    Node* temp = NULL; Node* current = *head_ref;
    while(current != NULL) { temp = current->prev; current->prev = current->next; current->next = temp; current = current->prev; }
    if(temp != NULL) *head_ref = temp->prev;
}

int detectCycle(Node* head) {
    Node* slow = head; Node* fast = head;
    while(fast != NULL && fast->next != NULL) { slow = slow->next; fast = fast->next->next; if(slow == fast) return 1; }
    return 0;
}

void removeCycle(Node* head) {
    Node* slow = head; Node* fast = head; int cycle =0;
    while(fast != NULL && fast->next != NULL) { slow = slow->next; fast = fast->next->next; if(slow == fast) { cycle =1; break; } }
    if(!cycle) return;
    slow = head;
    if(slow == fast) { while(fast->next != slow) fast = fast->next; fast->next = NULL; }
    else { while(slow->next != fast->next) { slow = slow->next; fast = fast->next; } fast->next = NULL; }
}

void freeList(Node* head) {
    while(head != NULL) { Node* temp = head; head = head->next; free(temp); }
}

int main() {
    Node* head = NULL;
    head = insertEndD(head, 10); head = insertEndD(head, 20); head = insertEndD(head, 30);
    head = insertEndD(head, 40); head = insertEndD(head, 50);
    displayDListForward(head); displayDListBackward(head);
    reverseList(&head); printf("After reversing:\n"); displayDListForward(head); displayDListBackward(head);
    // Create cycle
    head->next->next->next->next->next = head->next->next;
    if(detectCycle(head)) printf("Cycle detected.\n");
    removeCycle(head); printf("After removing cycle:\n");
    displayDListForward(head);
    freeList(head);
    return 0;
}