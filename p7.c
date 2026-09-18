#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
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

    int completed = 0;
    int time = 0;

    float totalWT = 0;
    float totalTAT = 0;

    printf("\nGantt Chart: ");

    int lastProcess = -1;

    while (completed < n) {

        int shortest = -1;
        int minRemaining = 999999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time &&
                p[i].remaining > 0 &&
                p[i].remaining < minRemaining) {

                minRemaining = p[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        if (shortest != lastProcess) {
            printf("P%d ", p[shortest].pid);
            lastProcess = shortest;
        }

        p[shortest].remaining--;
        time++;

        if (p[shortest].remaining == 0) {

            p[shortest].ct = time;

            p[shortest].tat =
                p[shortest].ct - p[shortest].at;

            p[shortest].wt =
                p[shortest].tat - p[shortest].bt;

            totalWT += p[shortest].wt;
            totalTAT += p[shortest].tat;

            completed++;
        }
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