#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX], recStack[MAX];
int V;

/* Function to detect cycle using DFS */
int detectCycle(int v) {
    visited[v] = 1;
    recStack[v] = 1;

    for (int i = 0; i < V; i++) {
        if (graph[v][i]) {
            if (!visited[i] && detectCycle(i))
                return 1;
            else if (recStack[i])
                return 1;
        }
    }

    recStack[v] = 0;
    return 0;
}

int main() {
    int p, r;
    int allocation[MAX][MAX], request[MAX][MAX];

    printf("Enter number of processes: ");
    scanf("%d", &p);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    V = p + r;

    printf("\nEnter Allocation Matrix (Process holding Resource)\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Request Matrix (Process requesting Resource)\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &request[i][j]);

    /* Initialize graph */
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    /* Build RAG */
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {

            if (allocation[i][j] == 1)
                graph[p + j][i] = 1; // Resource → Process

            if (request[i][j] == 1)
                graph[i][p + j] = 1; // Process → Resource
        }
    }

    /* Initialize DFS arrays */
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        recStack[i] = 0;
    }

    /* Check cycle */
    int deadlock = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (detectCycle(i)) {
                deadlock = 1;
                break;
            }
        }
    }

    if (deadlock)
        printf("\nSystem is in DEADLOCK state.\n");
    else
        printf("\nSystem is DEADLOCK FREE.\n");

    return 0;
}