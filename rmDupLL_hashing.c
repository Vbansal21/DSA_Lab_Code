#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HASH_SIZE 1000

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) { Node* newNode = (Node*)malloc(sizeof(Node)); newNode->data = data; newNode->next = NULL; return newNode; }

Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data); if(head == NULL) return newNode;
    Node* temp = head; while(temp->next != NULL) temp = temp->next; temp->next = newNode;
    return head;
}

void displayList(Node* head) { while(head != NULL) { printf("%d -> ", head->data); head = head->next; } printf("NULL\n"); }

Node* removeDuplicatesWithHash(Node* head) {
    if(head == NULL) return head;
    bool* hashTable = (bool*)calloc(HASH_SIZE, sizeof(bool));
    Node* current = head; Node* prev = NULL;
    while(current != NULL) {
        if(hashTable[current->data]) { prev->next = current->next; free(current); current = prev->next; }
        else { hashTable[current->data] = true; prev = current; current = current->next; }
    }
    free(hashTable); return head;
}

Node* removeDuplicatesNoHash(Node* head) {
    if(head == NULL) return head;
    Node* current = head;
    while(current != NULL) {
        Node* runner = current;
        while(runner->next != NULL)
            if(runner->next->data == current->data) { Node* temp = runner->next; runner->next = runner->next->next; free(temp); }
            else runner = runner->next;
        current = current->next;
    }
    return head;
}

void freeList(Node* head) { while(head != NULL) { Node* temp = head; head = head->next; free(temp); } }

int main() {
    Node* head = NULL;
    head = insertEnd(head, 10); head = insertEnd(head, 20); head = insertEnd(head, 10);
    head = insertEnd(head, 30); head = insertEnd(head, 20); head = insertEnd(head, 40);
    displayList(head);
    head = removeDuplicatesWithHash(head);
    displayList(head);
    head = insertEnd(head, 20); head = insertEnd(head, 50);
    displayList(head);
    head = removeDuplicatesNoHash(head);
    displayList(head);
    freeList(head);
    return 0;
}