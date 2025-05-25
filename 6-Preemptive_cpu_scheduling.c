#include <stdio.h>

#define MAX 100

typedef struct {
    int bt, pr, at;      // burst time, priority, arrival time (assumed 0)
    int wt, tat;         // waiting time, turnaround time
    int remaining_bt;
    int completed;
} Process;

void round_robin(Process p[], int n, int quantum) {
    int time = 0, done;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
    }

    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0) {
                done = 0;
                if (p[i].remaining_bt > quantum) {
                    time += quantum;
                    p[i].remaining_bt -= quantum;
                } else {
                    time += p[i].remaining_bt;
                    p[i].wt = time - p[i].bt;
                    p[i].remaining_bt = 0;
                }
            }
        }
    } while (!done);

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\n--- Round Robin Scheduling ---\n");
    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, p[i].bt, p[i].wt, p[i].tat);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

void priority_scheduling(Process p[], int n) {
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        p[i].completed = 0;
        p[i].at = 0; // assuming all arrive at time 0
    }

    while (completed != n) {
        int idx = -1;
        int min_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].pr < min_priority && p[i].at <= time) {
                min_priority = p[i].pr;
                idx = i;
            }
        }

        if (idx != -1) {
            time += p[idx].bt;
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        } else {
            time++; // no process ready, advance time
        }
    }

    printf("\n--- Priority Scheduling (Preemptive) ---\n");
    printf("P\tBT\tPR\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, p[i].bt, p[i].pr, p[i].wt, p[i].tat);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, quantum;
    Process p[MAX], backup[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        backup[i] = p[i]; // backup for second scheduling
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &quantum);

    round_robin(p, n, quantum);
    priority_scheduling(backup, n);

    return 0;
}
