#include <stdio.h>

struct Process {
    int pid;
    int at;    
    int bt;    
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
    }
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int time = 0;
    float totalWT = 0, totalTAT = 0;
    printf("\nGantt Chart: ");
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        printf("P%d ", p[i].pid);

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
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