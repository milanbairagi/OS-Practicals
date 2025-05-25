#include <stdio.h>
#include <stdbool.h>

#define P 10  // Max number of processes
#define R 10  // Max number of resources

int main() {
    int n, m;  // Number of processes and resources
    int alloc[P][R], max[P][R], need[P][R], avail[R];
    bool finished[P] = {false};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Algorithm
    int safeSeq[P], count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
