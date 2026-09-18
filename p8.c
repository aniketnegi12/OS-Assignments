#include <stdio.h>

struct Process {
    int pid;
    int at;     
    int bt;     
    int priority;
    int remaining;
    int ct;      
    int wt;      
    int tat;     
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
        p[i].remaining = p[i].bt;
    }

    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }

    printf("Enter priorities:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].priority);
    }

    int completed = 0;
    int time = 0;
    int last = -1;

    float totalWT = 0;
    float totalTAT = 0;

    printf("\nGantt Chart: ");

    while (completed < n) {

        int highest = -1;
        int bestPriority = 999999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time &&
                p[i].remaining > 0 &&
                p[i].priority < bestPriority) {

                bestPriority = p[i].priority;
                highest = i;
            }
        }

        if (highest == -1) {
            time++;
            continue;
        }
        if (last != highest) {
            printf("P%d ", p[highest].pid);
            last = highest;
        }
        p[highest].remaining--;
        time++;

        if (p[highest].remaining == 0) {

            p[highest].ct = time;

            p[highest].tat =
                p[highest].ct - p[highest].at;

            p[highest].wt =
                p[highest].tat - p[highest].bt;

            totalWT += p[highest].wt;
            totalTAT += p[highest].tat;

            completed++;
        }
    }

    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }

    printf("\nAverage waiting time: %.2f",
           totalWT / n);

    printf("\nAverage turnaround time: %.2f\n",
           totalTAT / n);

    return 0;
}