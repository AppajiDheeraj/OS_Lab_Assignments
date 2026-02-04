#include <stdio.h>
#include <stdlib.h>

/* Simple bubble sort */
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

void C_LOOK(int request[], int n, int head) {
    int totalMovement = 0;
    int current = head;

    // Sort request queue
    sort(request, n);

    // Service requests >= Head
    for (int i = 0; i < n; i++) {
        if (request[i] >= head) {
            totalMovement += abs(current - request[i]);
            current = request[i];
        }
    }

    // Find minimum request
    int minRequest = request[0];

    // Jump to lowest request (circular)
    totalMovement += abs(current - minRequest);
    current = minRequest;

    // Service requests < Head
    for (int i = 0; i < n; i++) {
        if (request[i] < head) {
            totalMovement += abs(current - request[i]);
            current = request[i];
        }
    }

    printf("Total Head Movement using C-LOOK = %d\n", totalMovement);
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

    C_LOOK(request, n, head);

    return 0;
}
