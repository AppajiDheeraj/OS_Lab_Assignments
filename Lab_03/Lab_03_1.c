#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* File structure */
struct File {
    char name[50];          // File Name
    int reference_count;    // number of directories pointing to a file
};

/* Directory structure */
struct Directory {
    char name[50];
    struct File *file_ptr;
};


int main() {
    /* Step 1: Create file using initialization */
    struct File F = {"shared_file", 0};

    /* Step 2: Create directories */
    struct Directory D1 = {"DirA", NULL};
    struct Directory D2 = {"DirB", NULL};

    /* Step 3: Share file between directories */
    D1.file_ptr = &F;
    F.reference_count++;

    D2.file_ptr = &F;
    F.reference_count++;

    /* Step 4: Display status */
    printf("\n--- File Sharing Status ---\n");
    printf("File Name: %s\n", F.name);
    printf("Reference Count: %d\n", F.reference_count);

    printf("%s contains %s\n", D1.name, D1.file_ptr->name);
    printf("%s contains %s\n", D2.name, D2.file_ptr->name);

    /* Step 5: Remove file from one directory */
    printf("\nRemoving file from %s...\n", D1.name);
    D1.file_ptr = NULL;
    F.reference_count--;

    printf("Updated Reference Count: %d\n", F.reference_count);

    /* Step 6: Safe deletion */
    if (F.reference_count == 0) {
        printf("File deleted from system.\n");
    } else {
        printf("File still shared. Cannot delete.\n");
    }

    return 0;
}