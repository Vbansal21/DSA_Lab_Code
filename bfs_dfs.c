#include <stdio.h>
#include <stdlib.h>

typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if(!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if(!graph) {
        printf("Memory allocation error\n");
        exit(1);
    }
    graph->numVertices = numVertices;

    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    if(!graph->array) {
        printf("Memory allocation error\n");
        exit(1);
    }

    for(int i = 0; i < numVertices; i++)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void BFS(Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    if(!visited) {
        printf("Memory allocation error\n");
        exit(1);
    }

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    if(!queue) {
        printf("Memory allocation error\n");
        exit(1);
    }
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    while(front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        AdjListNode* temp = graph->array[currentVertex].head;
        while(temp) {
            int adjVertex = temp->dest;
            if(!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}

void DFSUtil(Graph* graph, int vertex, int* visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    AdjListNode* temp = graph->array[vertex].head;
    while(temp) {
        int adjVertex = temp->dest;
        if(!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

void DFS(Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));
    if(!visited) {
        printf("Memory allocation error\n");
        exit(1);
    }

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

void freeGraph(Graph* graph) {
    for(int i = 0; i < graph->numVertices; i++) {
        AdjListNode* temp = graph->array[i].head;
        while(temp) {
            AdjListNode* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->array);
    free(graph);
}

int main() {
    int numVertices = 6;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    BFS(graph, 0);
    DFS(graph, 0);

    freeGraph(graph);
    return 0;
}