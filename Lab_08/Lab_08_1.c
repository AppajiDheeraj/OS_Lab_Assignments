#include <stdio.h>

#define MAX_PARTITIONS 50
#define MAX_PROCESSES 50

int main(void) {
    int partitionSize[MAX_PARTITIONS];
    int processSize[MAX_PROCESSES];
    int partitionUsed[MAX_PARTITIONS] = {0};
    int allocatedPartition[MAX_PROCESSES];
    int internalFrag[MAX_PROCESSES];

    int m, n;
    int i, j;
    int totalInternalFrag = 0;

    printf("Fixed Partition Multiprogramming (Internal Fragmentation)\n");

    printf("Enter number of fixed partitions (max %d): ", MAX_PARTITIONS);
    if (scanf("%d", &m) != 1 || m <= 0 || m > MAX_PARTITIONS) {
        printf("Invalid number of partitions.\n");
        return 1;
    }

    printf("Enter sizes of %d partitions:\n", m);
    for (i = 0; i < m; i++) {
        if (scanf("%d", &partitionSize[i]) != 1 || partitionSize[i] <= 0) {
            printf("Invalid partition size.\n");
            return 1;
        }
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
        allocatedPartition[i] = -1;
        internalFrag[i] = 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (!partitionUsed[j] && partitionSize[j] >= processSize[i]) {
                partitionUsed[j] = 1;
                allocatedPartition[i] = j;
                internalFrag[i] = partitionSize[j] - processSize[i];
                totalInternalFrag += internalFrag[i];
                break;
            }
        }
    }

    printf("\nProcess\tP.Size\tPartition\tPart.Size\tStatus\t\tInt.Frag\n");
    for (i = 0; i < n; i++) {
        if (allocatedPartition[i] != -1) {
            int p = allocatedPartition[i];
            printf("P%-6d\t%-6d\t%-9d\t%-9d\tAllocated\t%d\n",
                   i + 1, processSize[i], p + 1, partitionSize[p], internalFrag[i]);
        } else {
            printf("P%-6d\t%-6d\t-\t\t-\t\tNot Allocated\t-\n",
                   i + 1, processSize[i]);
        }
    }

    printf("\nTotal Internal Fragmentation = %d\n", totalInternalFrag);

    return 0;
}