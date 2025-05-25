#include <stdio.h>

// ----- MFT Simulation -----
void mft() {
    int ms, ps, nop, n, i;
    int fragment, b[10], p[10];

    printf("\n--- MFT (Fixed Partition) ---\n");
    printf("Enter total memory size: ");
    scanf("%d", &ms);
    printf("Enter partition size: ");
    scanf("%d", &ps);

    n = ms / ps;
    printf("Number of partitions: %d\n", n);
    printf("Enter number of processes: ");
    scanf("%d", &nop);

    for (i = 0; i < nop; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &p[i]);
    }

    printf("\nProcess\tProcess Size\tPartition Size\tFragmentation\n");
    for (i = 0; i < n && i < nop; i++) {
        if (p[i] > ps) {
            printf("P%d\t%d\t\t--\t\tNot Allocated (Too big)\n", i + 1, p[i]);
        } else {
            fragment = ps - p[i];
            printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, p[i], ps, fragment);
        }
    }
}

// ----- MVT Simulation -----
void mvt() {
    int ms, i, temp, n = 0, p[10], total = 0;

    printf("\n--- MVT (Variable Partition) ---\n");
    printf("Enter total memory size: ");
    scanf("%d", &ms);
    temp = ms;

    while (1) {
        if (temp <= 0)
            break;

        printf("Enter size of process %d (0 to stop): ", n + 1);
        scanf("%d", &p[n]);

        if (p[n] == 0)
            break;

        if (p[n] <= temp) {
            printf("Process %d allocated.\n", n + 1);
            temp -= p[n];
            total += p[n];
            n++;
        } else {
            printf("Not enough memory for process %d\n", n + 1);
            break;
        }
    }

    printf("\nTotal memory allocated = %d", total);
    printf("\nTotal memory left = %d\n", temp);
}

int main() {
    mft();
    mvt();
    return 0;
}
