#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, child_pid2, child_pid3, child_pid5;
    int status;

    printf("Main process: PID=%d\n", getpid());
    // fflush();

    child_pid = fork(); // Создание процесса 2

    if (child_pid < 0) {
        perror("Error creating the process");
        exit(1);
    } else if (child_pid == 0) { // Код процесса 2
        printf("process 2: PID=%d, PPID=%d\n", getpid(), getppid());
        
        child_pid2 = fork(); // Попытка создать процесс 3
        if (child_pid2 == 0) {
            printf("process 3: PID=%d, PPID=%d\n", getpid(), getppid());
            // execl("/bin/ls", "ls", "-la", NULL);
            exit(0);
        } else {
            child_pid3 = fork(); // Попытка создать процесс 4
            if (child_pid3 == 0) {
                printf("process 4: PID=%d, PPID=%d\n", getpid(), getppid());
                exit(0);
            }
        }
        wait(NULL); // Ждем завершения процессов 3 и 4
        wait(NULL);
        exit(0);
    } else { // Код главного процесса после создания процесса 2
        child_pid5 = fork(); // Создание процесса 5
        if (child_pid5 == 0) { // Код процесса 5
            printf("process 5: PID=%d, PPID=%d\n", getpid(), getppid());

            if (fork() == 0) { // Создание процесса 6
                printf("process 6: PID=%d, PPID=%d\n", getpid(), getppid());
                exit(0);
            }
            wait(NULL); // Ждем завершения процесса 6
            exit(0);
        }
    }

    wait(NULL); // Ждем завершения процессов 2 и 5
    wait(NULL);

    return 0;
}
