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
    int n, quantum;

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

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int queue[1000];
    int front = 0;
    int rear = 0;

    int added[n];

    for (int i = 0; i < n; i++)
        added[i] = 0;

    int time = 0;
    int completed = 0;

    float totalWT = 0;
    float totalTAT = 0;

    printf("\nGantt Chart: ");

    while (completed < n) {

        for (int i = 0; i < n; i++) {
            if (!added[i] &&
                p[i].at <= time) {

                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int current = queue[front++];

        printf("P%d ", p[current].pid);

        int run;

        if (p[current].remaining < quantum)
            run = p[current].remaining;
        else
            run = quantum;

        for (int t = 0; t < run; t++) {

            p[current].remaining--;
            time++;

            for (int i = 0; i < n; i++) {
                if (!added[i] &&
                    p[i].at <= time) {

                    queue[rear++] = i;
                    added[i] = 1;
                }
            }
        }

        if (p[current].remaining > 0) {

            queue[rear++] = current;

        } else {

            p[current].ct = time;

            p[current].tat =
                p[current].ct - p[current].at;

            p[current].wt =
                p[current].tat - p[current].bt;

            totalWT += p[current].wt;
            totalTAT += p[current].tat;

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

    printf("\nAverage waiting time: %.2f",
           totalWT / n);

    printf("\nAverage turnaround time: %.2f\n",
           totalTAT / n);

    return 0;
}