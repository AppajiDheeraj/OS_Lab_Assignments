#include <stdio.h>
#include <stdlib.h>

#define MAX 199   // Maximum disk size (0 to MAX)

/* This is required in case of qsort() */

// int compare(const void *a, const void *b) {
//     return (*(int *)a - *(int *)b);
// }

void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void C_SCAN(int request[], int n, int head) {
    int totalMovement = 0;
    int current = head;

    // Sort the request queue
    sort(request,n);

    // Service requests >= Head
    for (int i = 0; i < n; i++) {
        if (request[i] >= head) {
            totalMovement += abs(current - request[i]);
            current = request[i];
        }
    }

    // Move to end of disk
    totalMovement += abs(current - MAX);
    current = MAX;

    // Jump from MAX to 0
    totalMovement += abs(MAX - 0);
    current = 0;

    // Service requests < Head
    for (int i = 0; i < n; i++) {
        if (request[i] < head) {
            totalMovement += abs(current - request[i]);
            current = request[i];
        }
    }

    printf("Total Head Movement using C-SCAN = %d\n", totalMovement);
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

    C_SCAN(request, n, head);

    return 0;
}
