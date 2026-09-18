#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int completed;
};

int main() {
        printf("Name: Aniket Singh Negi | Section: A2 | Roll No: 09\n");

    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }

    int completed = 0;
    int time = 0;

    float totalWT = 0;
    float totalTAT = 0;

    printf("\nGantt Chart: ");

    while (completed < n) {

        int shortest = -1;
        int minBT = 999999;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed &&
                p[i].at <= time &&
                p[i].bt < minBT) {

                minBT = p[i].bt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        printf("P%d ", p[shortest].pid);

        time += p[shortest].bt;

        p[shortest].ct = time;
        p[shortest].tat = p[shortest].ct - p[shortest].at;
        p[shortest].wt = p[shortest].tat - p[shortest].bt;

        totalWT += p[shortest].wt;
        totalTAT += p[shortest].tat;

        p[shortest].completed = 1;
        completed++;
    }

    printf("\n\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}