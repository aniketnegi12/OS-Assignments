#include <stdio.h>
#include <unistd.h>
int main() {
printf("Name: Aniket Singh  Negi | Section: A2 | Roll No: 09\n");
pid_t pid = fork();
if (pid < 0) {
printf("Fork failed\n");
} else if (pid == 0) {
printf("Child process created successfully\n");
} else {
printf("Parent process created successfully\n");
}
return 0;
}
