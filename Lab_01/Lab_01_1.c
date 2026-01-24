#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if(pid < 0){
        perror("Fork failed");
        exit(1);
    }

    else if(pid == 0){
        printf("\n--- Child Process ---\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Child process exiting...\n");
        exit(0);   // Terminate child
    }

    else {
        wait(NULL);
        printf("%d",pid);
        printf("\n--- Parent Process ---\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child completed execution\n");
    }

    return 0;
}
