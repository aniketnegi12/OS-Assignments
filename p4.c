#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
int main() {
printf("Name: Aniket Singh Negi | Section: A2 | Roll No: 09\n");
DIR *dir;
struct dirent *entry;
struct stat fileStat;
dir = opendir(".");
if (dir == NULL) {
printf("Unable to open directory\n");
return 1;}
printf("\nFile Name\tType\tSize\tPermissions\n");
while ((entry = readdir(dir)) != NULL) {
if (stat(entry->d_name, &fileStat) == -1) {
continue;
}
printf("%s\t\t", entry->d_name);
if (S_ISDIR(fileStat.st_mode))
printf("Directory\t");
else if (S_ISREG(fileStat.st_mode))
printf("File\t\t");
else
printf("Other\t\t");
printf("%lld\t", fileStat.st_size);
printf("%c%c%c%c%c%c%c%c%c\n",
(fileStat.st_mode & S_IRUSR) ? 'r' : '-',
(fileStat.st_mode & S_IWUSR) ? 'w' : '-',
(fileStat.st_mode & S_IXUSR) ? 'x' : '-',
(fileStat.st_mode & S_IRGRP) ? 'r' : '-',
(fileStat.st_mode & S_IWGRP) ? 'w' : '-',
(fileStat.st_mode & S_IXGRP) ? 'x' : '-',
(fileStat.st_mode & S_IROTH) ? 'r' : '-',
(fileStat.st_mode & S_IWOTH) ? 'w' : '-',
(fileStat.st_mode & S_IXOTH) ? 'x' : '-');}
closedir(dir);
return 0;
}
