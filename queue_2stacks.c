#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Stack {
    int data[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int value) {
    if(s->top == MAX_SIZE -1) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    s->data[++(s->top)] = value;
}

int pop(Stack *s) {
    if(isEmpty(s)) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;
    }
    return s->data[(s->top)--];
}

void display(Stack *s) {
    if(isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements: ");
    for(int i = 0; i <= s->top; i++)
        printf("%d ", s->data[i]);
    printf("\n");
}

typedef struct QueueUsingStacks {
    Stack stack1;
    Stack stack2;
} QueueUsingStacks;

void initializeQueue(QueueUsingStacks *q) {
    initialize(&(q->stack1));
    initialize(&(q->stack2));
}

void enqueue(QueueUsingStacks *q, int value) {
    while(!isEmpty(&(q->stack1))) {
        push(&(q->stack2), pop(&(q->stack1)));
    }
    push(&(q->stack1), value);
    while(!isEmpty(&(q->stack2))) {
        push(&(q->stack1), pop(&(q->stack2)));
    }
    printf("Enqueued %d\n", value);
}

int dequeue(QueueUsingStacks *q) {
    if(isEmpty(&(q->stack1))) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    return pop(&(q->stack1));
}

void displayQueue(QueueUsingStacks *q) {
    if(isEmpty(&(q->stack1))) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for(int i = 0; i <= q->stack1.top; i++)
        printf("%d ", q->stack1.data[i]);
    printf("\n");
}

int main() {
    QueueUsingStacks q;
    initializeQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));

    return 0;
}
