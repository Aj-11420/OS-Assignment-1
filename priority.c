#include <stdio.h>
#include <string.h>

struct process {
    char pid[10];
    int at;   // Arrival Time
    int bt;   // Burst Time
    int pr;   // Priority
    int ct;   // Completion Time
    int wt;   // Waiting Time
    int tat;  // Turnaround Time
    int done; // Process finished flag
};

int main() {

    int n;
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].done = 0;
    }

    int completed = 0, time = 0;
    float total_wt = 0, total_tat = 0;

    while(completed < n) {

        int idx = -1;
        int highest_pr = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].done == 0) {
                if(p[i].pr > highest_pr) {
                    highest_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
        } 
        else {
            time += p[idx].bt;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;

            p[idx].done = 1;
            completed++;
        }
    }

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].wt);

    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].tat);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
