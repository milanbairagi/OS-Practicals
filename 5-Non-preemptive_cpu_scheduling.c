#include <stdio.h>

typedef struct {
    int bt;   // Burst time
    int wt;   // Waiting time
    int tat;  // Turnaround time
    int pr;   // Priority (for Priority Scheduling)
} Process;

void calculate_fcfs(int n, Process p[]) {
    p[0].wt = 0;  // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].bt + p[i-1].wt;
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\n--- FCFS Scheduling ---\n");
    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, p[i].bt, p[i].wt, p[i].tat);
    
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

void calculate_sjf(int n, Process p[]) {
    int temp_bt, temp_pr;
    // Sorting based on burst time for SJF (shortest job first)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].bt > p[j].bt) {
                temp_bt = p[i].bt;
                p[i].bt = p[j].bt;
                p[j].bt = temp_bt;
            }
        }
    }

    p[0].wt = 0;  // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].bt + p[i-1].wt;
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\n--- SJF Scheduling ---\n");
    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, p[i].bt, p[i].wt, p[i].tat);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

void calculate_priority(int n, Process p[]) {
    Process temp;
    // Sorting based on priority
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].pr > p[j].pr) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wt = 0;  // First process has 0 waiting time
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].bt + p[i-1].wt;
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\n--- Priority Scheduling ---\n");
    printf("P\tBT\tWT\tTAT\tPriority\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, p[i].bt, p[i].wt, p[i].tat, p[i].pr);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    printf("Enter Burst Time and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d:\n", i+1);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].pr);  // Only required for priority scheduling
    }

    calculate_fcfs(n, p);
    calculate_sjf(n, p);
    calculate_priority(n, p);

    return 0;
}
