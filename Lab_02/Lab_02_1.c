#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define DISK_SIZE 10

void printDiskState(int disk[]){
    printf("Disk Status: ");
    for(int i=0; i<DISK_SIZE; i++){
        printf(" %d",disk[i]);
    }
    printf("\n");
}

bool isContinousFree(int disk[], int start, int length){
    if(start + length > DISK_SIZE){
        return false;
    }
    for(int i=start; i<start + length; i++){
        if(disk[i]!=0) return false;
    }
    return true;
}

int main(){
    int disk[DISK_SIZE] = {0};
    int file_start, file_end,grow_by;
    printf("Enter disk status (0 = free, 1 = occupied):\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        scanf("%d", &disk[i]);
    }

    printf("\nEnter the file start (0-9): ");
    scanf("%d",&file_start);
    printf("\nEnter the file end (0-9): ");
    scanf("%d",&file_end);
    printf("\nEnter the number of blocks by which you want the file to grow: ");
    scanf("%d", &grow_by);

    printf("\n-------Current Disk State----------\n");
    printDiskState(disk);

    int currentSize = file_end - file_start + 1;
    int newSize = currentSize + grow_by;

    if(isContinousFree(disk,file_end + 1,grow_by)){
        for (int i = file_end + 1; i <= file_end + grow_by; i++)
            disk[i] = 1;
        printf("\nAllocation Successful!\n");
        printf("File now occupies blocks (%d - %d)\n",
               file_start, file_end + grow_by);
    }else {
        int relocated = 0;

        for(int j = file_start; j <= file_end; j++) {
            disk[j] = 0;
        }

        for(int i=0 ; i<=DISK_SIZE - newSize; i++){
           if (isContinousFree(disk, i, newSize)){

            for (int j = i; j < i + newSize; j++) {
                disk[j] = 1;
            }

            printf("\nRelocation Successful!\n");
            printf("File relocated to blocks (%d - %d)\n",i, i + newSize - 1);
            relocated = 1;
            break;
           }
        }

        if(relocated != 1){
            for(int j = file_start; j <= file_end; j++) {
                disk[j] = 1;
            }
            printf("\nAllocation Failed!\n");
            printf("No contiguous space available.\n");
        }
    }

    printf("\n---------Final Disk State--------------\n");
    printDiskState(disk);
    return 0;
}