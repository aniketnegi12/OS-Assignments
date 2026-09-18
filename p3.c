#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
 
int main() {
    printf("Name: Aniket Singh  Negi | Section: A2 | Roll No: 09\n");
    pid_t pid = fork();
 
    if (pid < 0) { 
        printf("Fork failed\n"); 
        return 1; 
    }
 
    if (pid == 0) {
        printf("Child process started. PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        sleep(3);
        printf("Child process after parent exit. New Parent PID: %d\n", getppid());
        exit(0);
    } else {
        printf("Parent process started. PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        sleep(1);
        printf("Parent process exiting...\n");
        exit(0);
    }
    return 0;
}
