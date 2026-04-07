#include <stdio.h>

#define MAX 20

void nextFit(int blocks[], int n, int processes[], int m) {
    int tempBlocks[MAX], allocation[MAX], originalSize[MAX], frag[MAX];
    int totalInternal = 0, totalExternal = 0;
    int lastIdx = 0;

    for (int i = 0; i < n; i++) tempBlocks[i] = blocks[i];
    for (int i = 0; i < m; i++) allocation[i] = -1;

    printf("\n--- Next-Fit Allocation ---\n");
    for (int i = 0; i < m; i++) {
        int count = 0;
        while (count < n) {
            if (tempBlocks[lastIdx] >= processes[i]) {
                allocation[i] = lastIdx;
                originalSize[i] = tempBlocks[lastIdx];
                frag[i] = tempBlocks[lastIdx] - processes[i];
                tempBlocks[lastIdx] -= processes[i];
                break;
            }
            lastIdx = (lastIdx + 1) % n;
            count++;
        }
    }

    printf("P_No\tP_Size\tBlock_No\tBlock_Size\tFragment\n");
    for (int i = 0; i < m; i++) {
        printf("%d\t%d\t", i + 1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\t\t%d\t\t%d\n", allocation[i] + 1, originalSize[i], frag[i]);
            totalInternal += frag[i];
        } else printf("Not Allocated\n");
    }

    for (int i = 0; i < n; i++) totalExternal += tempBlocks[i];
    printf("Total Internal Fragmentation: %d KB\n", totalInternal);
    printf("Total External Fragmentation: %d KB\n", totalExternal);
}

int main() {
    int n, m, totalMem, sumBlocks = 0;
    int blocks[MAX], processes[MAX];

    printf("Enter total memory size: ");
    scanf("%d", &totalMem);
    printf("Enter number of memory blocks: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Size of block %d: ", i + 1);
        scanf("%d", &blocks[i]);
        sumBlocks += blocks[i];
    }

    if (sumBlocks > totalMem) {
        printf("Error: Blocks exceed total memory!\n");
        return 0;
    }

    printf("Enter number of processes: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        printf("Requirement of process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }

    nextFit(blocks, n, processes, m);
    return 0;
}