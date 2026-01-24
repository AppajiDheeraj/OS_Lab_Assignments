#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void file_operations(){
    int fd;
    char buffer[1200];
    char text[1000];
    char filename[100];

    printf("File Name: ");
    fgets(filename, sizeof(filename),stdin);
    filename[strcspn(filename,"\n")] = '\0';

    fd = open(filename, O_CREAT | O_RDWR, 0644);

    if( fd == -1) {
        perror("Error opening file");
        return;
    }

    printf("File created successfully\n");

    printf("Enter text to write into file:\n");
    fgets(text, sizeof(text), stdin);

    write(fd,text, strlen(text));
    printf("Data written to file\n");
    lseek(fd, 0, SEEK_SET);

    int byteReads = read(fd, buffer, sizeof(buffer)-1);
    buffer[byteReads] = '\0';

    printf("\nFile Content:\n%s\n", buffer);

    // Close file
    close(fd);
    printf("File closed successfully\n");
}

void main(){
    file_operations();
}