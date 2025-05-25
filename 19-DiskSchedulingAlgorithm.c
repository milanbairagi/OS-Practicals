#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    // Simple bubble sort for sorting
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

void fcfs(int requests[], int n, int head) {
    int seek = 0;
    printf("\n[FCFS] Order: %d ", head);
    for (int i = 0; i < n; i++) {
        seek += abs(requests[i] - head);
        head = requests[i];
        printf("-> %d ", head);
    }
    printf("\nTotal Seek Time: %d\n", seek);
}

void scan(int requests[], int n, int head, int disk_size) {
    int seek = 0;
    int i;
    int left[100], right[100];
    int l = 0, r = 0;

    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\n[SCAN] Order: %d ", head);
    for (i = 0; i < r; i++) {
        seek += abs(head - right[i]);
        head = right[i];
        printf("-> %d ", head);
    }

    seek += abs(head - (disk_size - 1));
    head = disk_size - 1;
    printf("-> %d ", head);

    for (i = l - 1; i >= 0; i--) {
        seek += abs(head - left[i]);
        head = left[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time: %d\n", seek);
}

void look(int requests[], int n, int head) {
    int seek = 0;
    int i;
    int left[100], right[100];
    int l = 0, r = 0;

    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\n[LOOK] Order: %d ", head);
    for (i = 0; i < r; i++) {
        seek += abs(head - right[i]);
        head = right[i];
        printf("-> %d ", head);
    }

    for (i = l - 1; i >= 0; i--) {
        seek += abs(head - left[i]);
        head = left[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time: %d\n", seek);
}

// ----------- Main Function -------------
int main() {
    int requests[100], n, head, disk_size;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    fcfs(requests, n, head);
    scan(requests, n, head, disk_size);
    look(requests, n, head);

    return 0;
}
