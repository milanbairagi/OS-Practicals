#include <stdio.h>

int main() {
    int frames[10], freq[10], pages[30];
    int n, f, i, j, k, pos, min, pageFaults = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }

    printf("\nPage\tFrames\n");

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in frame
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            pos = -1;
            min = 9999;

            // Find least frequently used
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                } else if (freq[j] < min) {
                    min = freq[j];
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            freq[pos] = 1;
            pageFaults++;
        }

        // Display current frame state
        printf("%d\t", pages[i]);
        for (k = 0; k < f; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
