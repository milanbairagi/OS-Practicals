#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int f, int current) {
    int farthest = current, pos = -1;
    
    for (int i = 0; i < f; i++) {
        int j;
        for (j = current + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) {
            return i; // If page not found, replace it
        }
    }
    return pos;
}

int main() {
    int frames[10], pages[30], n, f, i, j, k, pos, pageFaults = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1; // Initially all frames are empty
    }

    printf("\nPage\tFrames\n");

    for (i = 0; i < n; i++) {
        found = 0;

        // Check if page is already in one of the frames
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // If no empty frame or page not found, replace the optimal page
            pos = findOptimal(pages, frames, n, f, i);
            frames[pos] = pages[i];
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
