#include<stdio.h>
#include <stdbool.h>

#define DISK_SIZE 10
#define MAX_INDEX 10

void printDisk(int disk[]) {
    printf("Disk Status: ");
    for (int i = 0; i < DISK_SIZE; i++)
        printf("%d ", disk[i]);
    printf("\n");
}

void printIndexBlock(int index[], int count) {
    printf("Index Block -> ");
    for (int i = 0; i < count; i++)
        printf("%d ", index[i]);
    printf("\n");
}

int main(){

    int disk[DISK_SIZE] = {0};
    int indexBlock[MAX_INDEX];
    int indexCount;
    int grow_by;

    printf("Enter disk status (0 = free, 1 = occupied):\n");
    for (int i = 0; i < DISK_SIZE; i++)
        scanf("%d", &disk[i]);

    printf("\nEnter number of blocks in index block: ");
    scanf("%d", &indexCount);

    printf("Enter the block numbers in index block:\n");
    for (int i = 0; i < indexCount; i++)
        scanf("%d", &indexBlock[i]);

    printf("\nEnter number of blocks to grow: ");
    scanf("%d", &grow_by);

    printf("\n--- Initial State ---\n");
    printDisk(disk);
    printIndexBlock(indexBlock, indexCount);

    int found = 0;
    int tempCount = 0;
    int tempBlock[MAX_INDEX];


    for(int i = 0; i < DISK_SIZE && tempCount < grow_by; i++) {
        if(disk[i] == 0) {
            tempBlock[tempCount++] = i;
        }
    }

    if(tempCount == grow_by){
        for(int i=0; i < tempCount; i++){
            indexBlock[indexCount++] = tempBlock[i];
            disk[tempBlock[i]] = 1;
        }
        printf("\nAllocation Successful!\n");
        printIndexBlock(indexBlock, indexCount);
    } else {
        printf("\nAllocation Failed!\n");
        printf("Not enough free blocks available.\n");
    }
    
    printf("\n----------Final Disk State-----------\n");
    printDisk(disk);

    return 0;
}