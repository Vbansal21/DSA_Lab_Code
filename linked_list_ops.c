#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node* insertHead(Node* head, int value) {
    Node* newNode = createNode(value);
    newNode->next = head;
    head = newNode;
    printf("Inserted %d at head.\n", value);
    return head;
}

Node* insertTail(Node* head, int value) {
    Node* newNode = createNode(value);
    if(head == NULL) {
        head = newNode;
        printf("Inserted %d as head (since list was empty).\n", value);
        return head;
    }
    Node* temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    printf("Inserted %d at tail.\n", value);
    return head;
}

Node* deleteNode(Node* head, int key) {
    if(head == NULL) {
        printf("List is empty. Cannot delete %d.\n", key);
        return head;
    }
    if(head->data == key) {
        Node* temp = head;
        head = head->next;
        free(temp);
        printf("Deleted %d from head.\n", key);
        return head;
    }
    Node* current = head->next;
    Node* prev = head;
    while(current != NULL && current->data != key) {
        prev = current;
        current = current->next;
    }
    if(current == NULL) {
        printf("Element %d not found in the list.\n", key);
        return head;
    }
    prev->next = current->next;
    free(current);
    printf("Deleted %d from the list.\n", key);
    return head;
}

void displayList(Node* head) {
    if(head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Linked List: ");
    Node* temp = head;
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    head = insertHead(head, 10);
    head = insertHead(head, 20);
    head = insertTail(head, 30);
    head = insertTail(head, 40);
    displayList(head);

    head = deleteNode(head, 20);
    displayList(head);

    head = deleteNode(head, 50);
    displayList(head);

    freeList(head);
    return 0;
}
