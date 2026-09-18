#include <stdio.h>
#include <unistd.h>
int main() {
    printf("Name: Aniket Singh Negi | Section: A2 | Roll No: 09\n");
    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    if (pid == 0) {
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    } else {
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);
    }
    return 0;
}

