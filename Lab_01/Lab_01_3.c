#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    int *arr;
    int n = 5;

    //Get the generic pointer to the memory address of the top of the stack 
    void *initial_brk = sbrk(0);
    
    printf("Initial Memory addess: %p\n",sbrk(0));
    void *final_brk = initial_brk + n*sizeof(int);
    printf("Final Memory addess: %p\n",final_brk);
    printf("Memory Increased to %ld\n",final_brk - initial_brk);
    brk(final_brk);
    //Type cast to int pointer
    arr = (int *)initial_brk;

    for(int i=0; i<n; i++){
        arr[i] = (i+1)*5;
    }

    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }

    printf("\n");
    brk(initial_brk);
    return 0;
}