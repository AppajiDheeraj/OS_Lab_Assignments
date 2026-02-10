#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void LOOK(int request[], int n, int head) {
    int totalMovement = 0;
    int current = head;

    // Sort the request queue
    qsort(request, n, sizeof(int), compare);

    // Move towards higher tracks first
    for (int i = 0; i < n; i++) {
        if (request[i] >= head) {
            totalMovement += abs(current - request[i]);
            current = request[i];
        }
    }

    // Reverse direction and move towards lower tracks
    for (int i = n - 1; i >= 0; i--) {
        if (request[i] < head) {
            totalMovement += abs(current - request[i]);
            current = request[i];
        }
    }

    printf("Total Head Movement using LOOK = %d\n", totalMovement);
    printf("Average Seek Time = %.2f\n", (float)totalMovement / n);
}

int main() {
    int n, head;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    LOOK(request, n, head);

    return 0;
}
