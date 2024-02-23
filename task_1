#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main() {
    pid_t child_pid;
    int status;

    child_pid = fork();

    if(child_pid < 0){
        perror("Error in creating process");
        exit(1);
    }

    if(child_pid == 0){
        printf("Child pid = %d\n", getpid());
        exit(0);
    } else {
        printf("Parent pid = %d\n", getpid());
        wait(&status);
        printf("Status = %d\n", WEXITSTATUS(status));
    }
    return 0;
}

