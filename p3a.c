#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
printf("Name: Aniket Singh  Negi\tSection: A2\tRoll No:09\n");
pid_t pid = fork();
if (pid < 0) {
printf("Fork failed\n");
return 1;
}
if (pid == 0) {
printf("Child process exiting...\n");
exit(0);
} else {
printf("Parent process waiting...\n");
sleep(5);
wait(NULL);
printf("Child process collected by parent using wait()\n");
}
return 0;
}
