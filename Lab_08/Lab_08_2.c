#include <stdio.h>

#define MAX_BLOCKS 50
#define MAX_PROCESSES 50

int main(void) {
    int blockSize[MAX_BLOCKS];
    int remaining[MAX_BLOCKS];
    int processSize[MAX_PROCESSES];
    int allocatedBlock[MAX_PROCESSES];

    int m, n;
    int i, j;
    int totalFree = 0;
    int largestHole = 0;
    int externalFragExists = 0;

    printf("Variable Partition Allocation - First Fit (External Fragmentation)\n");

    printf("Enter number of memory blocks (max %d): ", MAX_BLOCKS);
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_BLOCKS) {
        printf("Invalid number of memory blocks.\n");
        return 1;
    }

    printf("Enter sizes of %d blocks:\n", m);
    for (i = 0; i < m; i++) {
        if (scanf("%d", &blockSize[i]) != 1 || blockSize[i] <= 0) {
            printf("Invalid block size.\n");
            return 1;
        }
        remaining[i] = blockSize[i];
    }

    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter sizes of %d processes:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &processSize[i]) != 1 || processSize[i] <= 0) {
            printf("Invalid process size.\n");
            return 1;
        }
        allocatedBlock[i] = -1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (remaining[j] >= processSize[i]) {
                remaining[j] -= processSize[i];
                allocatedBlock[i] = j;
                break;
            }
        }
    }

    printf("\nProcess\tP.Size\tBlock\tStatus\n");
    for (i = 0; i < n; i++) {
        if (allocatedBlock[i] != -1) {
            printf("P%-6d\t%-6d\tB%-4d\tAllocated\n", i + 1, processSize[i], allocatedBlock[i] + 1);
        } else {
            printf("P%-6d\t%-6d\t-\tNot Allocated\n", i + 1, processSize[i]);
        }
    }

    for (i = 0; i < m; i++) {
        totalFree += remaining[i];
        if (remaining[i] > largestHole) {
            largestHole = remaining[i];
        }
    }

    for (i = 0; i < n; i++) {
        if (allocatedBlock[i] == -1 && processSize[i] <= totalFree && processSize[i] > largestHole) {
            externalFragExists = 1;
            break;
        }
    }

    printf("\nFree memory in blocks after allocation:\n");
    for (i = 0; i < m; i++) {
        printf("Block B%d: %d\n", i + 1, remaining[i]);
    }

    printf("\nTotal Free Memory = %d\n", totalFree);
    printf("Largest Free Block = %d\n", largestHole);

    if (externalFragExists) {
        printf("External Fragmentation Exists\n");
    } else {
        printf("External Fragmentation Does Not Exist\n");
    }

    return 0;
}