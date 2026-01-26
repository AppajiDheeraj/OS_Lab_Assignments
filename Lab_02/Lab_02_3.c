#include <stdio.h>

#define DISK_SIZE 10
#define NULL_PTR -1

struct Block {
    int used;
    int next;
};

struct Directory {
    int start;
    int end;
};

void printDisk(struct Block disk[]) {
    printf("\nDisk State:\n");
    printf("Block : ");
    for(int i = 0; i < DISK_SIZE; i++)
        printf("%2d ", i);

    printf("\nUsed  : ");
    for(int i = 0; i < DISK_SIZE; i++)
        printf("%2d ", disk[i].used);

    printf("\nNext  : ");
    for(int i = 0; i < DISK_SIZE; i++)
        printf("%2d ", disk[i].next);

    printf("\n");
}

void printFile(struct Directory dir, struct Block disk[]) {
    printf("\nFile Blocks: ");
    int cur = dir.start;

    while (cur != NULL_PTR) {
        printf("%d", cur);
        cur = disk[cur].next;
        if (cur != NULL_PTR)
            printf(" -> ");
    }
    printf("\n");
}

int main() {
    struct Block disk[DISK_SIZE];
    struct Directory file;

    // Step 1: Input disk state
    printf("Enter disk state (0 = free, 1 = occupied):\n");
    for(int i = 0; i < DISK_SIZE; i++) {
        scanf("%d", &disk[i].used);
        disk[i].next = NULL_PTR;
    }

    int n;
    printf("\nEnter number of blocks in file: ");
    scanf("%d", &n);

    printf("Enter starting block: ");
    scanf("%d", &file.start);

    if (disk[file.start].used == 0) {
        printf("Invalid start block!\n");
        return 0;
    }

    int prev = file.start;

    printf("Enter remaining file blocks:\n");
    for (int i = 1; i < n; i++) {
        int b;
        scanf("%d", &b);

        if (disk[b].used == 0) {
            printf("Block %d is free. Invalid file block!\n", b);
            return 0;
        }

        disk[prev].next = b;
        prev = b;
    }

    file.end = prev;

    int grow;
    printf("\nEnter number of blocks to grow: ");
    scanf("%d", &grow);

    int added = 0;

    for (int i = 0; i < DISK_SIZE && added < grow; i++) {
        if (disk[i].used == 0) {
            disk[i].used = 1;
            disk[i].next = NULL_PTR;
            disk[file.end].next = i;
            file.end = i;
            added++;
        }
    }

    if (added == grow)
        printf("\nAllocation Successful!\n");
    else
        printf("\nAllocation Failed! Not enough space.\n");

    printDisk(disk);
    printFile(file, disk);
    printf("\nDirectory Entry:");
    printf("\nStart Block: %d", file.start);
    printf("\nEnd Block  : %d\n", file.end);

    return 0;
}
