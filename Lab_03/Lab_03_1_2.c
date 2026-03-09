#include <stdio.h>
#include <string.h>

#define MAX_FILES 5
#define MAX_SUBDIRS 3

/* File structure */
struct File {
    char name[50];
    int reference_count;
};

/* Directory structure */
struct Directory {
    char name[50];

    struct File *files[MAX_FILES];
    int file_count;

    struct Directory *subdirs[MAX_SUBDIRS];
    int subdir_count;
};


/* Function to add file to directory */
void addFile(struct Directory *dir, struct File *file) {
    if (dir->file_count < MAX_FILES) {
        dir->files[dir->file_count++] = file;
        file->reference_count++;
    }
}

/* Function to add subdirectory */
void addSubDir(struct Directory *parent, struct Directory *child) {
    if (parent->subdir_count < MAX_SUBDIRS) {
        parent->subdirs[parent->subdir_count++] = child;
    }
}


/* Function to print directory structure */
void printDirectory(struct Directory *dir, int level) {
    for (int i = 0; i < level; i++)
        printf("  ");

    printf("Directory: %s\n", dir->name);

    /* Print files */
    for (int i = 0; i < dir->file_count; i++) {
        for (int j = 0; j < level + 1; j++)
            printf("  ");
        printf("|--File: %s (RefCount: %d)\n",
               dir->files[i]->name,
               dir->files[i]->reference_count);
    }

    /* Print subdirectories recursively */
    for (int i = 0; i < dir->subdir_count; i++) {
        printDirectory(dir->subdirs[i], level + 1);
    }
}

int main() {

    /* Create files */
    struct File F1 = {"file1.txt", 0};
    struct File F2 = {"file2.txt", 0};
    struct File F3 = {"shared.txt", 0};

    /* Create directories */
    struct Directory root = {"root", {NULL}, 0, {NULL}, 0};
    struct Directory sub1 = {"subdir1", {NULL}, 0, {NULL}, 0};
    struct Directory sub2 = {"subdir2", {NULL}, 0, {NULL}, 0};

    /* Build hierarchy */
    addSubDir(&root, &sub1);
    addSubDir(&root, &sub2);

    /* Add files */
    addFile(&root, &F1);
    addFile(&sub1, &F2);

    /* Share file across directories */
    addFile(&root, &F3);
    addFile(&sub2, &F3);  // shared file

    /* Print structure */
    printf("\n--- File System Structure ---\n");
    printDirectory(&root, 0);

    return 0;
}