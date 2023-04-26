#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    printf("The pid of the parent program is : %d\n", getppid());

    fork();
    printf("Hello world!\n");
    return 0;
}