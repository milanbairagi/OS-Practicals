#include <stdio.h>

int main() {
    int pageTable[20], i, n, frameSize, logicalAddr;
    int pageNumber, offset, physicalAddr;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter frame (page) size: ");
    scanf("%d", &frameSize);

    printf("Enter page table (frame number for each page):\n");
    for (i = 0; i < n; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    printf("\nEnter a logical address (0 to %d): ", n * frameSize - 1);
    scanf("%d", &logicalAddr);

    pageNumber = logicalAddr / frameSize;
    offset = logicalAddr % frameSize;

    if (pageNumber >= n) {
        printf("Invalid logical address!\n");
    } else {
        physicalAddr = pageTable[pageNumber] * frameSize + offset;
        printf("Physical Address = %d\n", physicalAddr);
    }

    return 0;
}
