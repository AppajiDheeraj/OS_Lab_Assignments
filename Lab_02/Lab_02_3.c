#include<stdio.h>
#include<stdbool.h>

#define DISK_SIZE 10
#define MAX_BLOCKS 10

void printDiskState(int disk[]){
    printf("Disk Status: ");
    for(int i=0; i<DISK_SIZE; i++){
        printf(" %d",disk[i]);
    }
    printf("\n");
}

void printLinkedList(int linkedList[], int count){
    printf("File blocks (linked): ");
    for(int i=0; i<count; i++){
        printf("%d", linkedList[i]);
        if(i < count - 1) printf(" -> ");
    }
    printf("\n");
}

int main(){
    int disk[DISK_SIZE] = {0};
    int linkedList[MAX_BLOCKS];
    int fileBlockCount;
    int grow_by;

    printf("Enter disk status (0 = free, 1 = occupied):\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        scanf("%d", &disk[i]);
    }

    printf("\nEnter number of blocks currently in file: ");
    scanf("%d", &fileBlockCount);

    printf("Enter the linked block numbers (e.g., 2 5 7):\n");
    for (int i = 0; i < fileBlockCount; i++) {
        scanf("%d", &linkedList[i]);
    }

    printf("\nEnter the number of blocks by which you want the file to grow: ");
    scanf("%d", &grow_by);

    printf("\n-------Current Disk State----------\n");
    printDiskState(disk);
    printLinkedList(linkedList, fileBlockCount);

    int freeBlocksFound = 0;
    int tempBlocks[MAX_BLOCKS];

    // Find free blocks
    for(int i = 0; i < DISK_SIZE && freeBlocksFound < grow_by; i++) {
        if(disk[i] == 0) {
            tempBlocks[freeBlocksFound++] = i;
        }
    }

    if(freeBlocksFound == grow_by) {
        // Allocate the new blocks
        for(int i = 0; i < grow_by; i++) {
            linkedList[fileBlockCount++] = tempBlocks[i];
            disk[tempBlocks[i]] = 1;
        }
        printf("\nAllocation Successful!\n");
        printf("File now links to new blocks\n");
    } else {
        printf("\nAllocation Failed!\n");
        printf("Not enough free blocks available.\n");
    }

    printf("\n---------Final Disk State--------------\n");
    printDiskState(disk);
    printLinkedList(linkedList, fileBlockCount);

    return 0;
}