#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

// Simulate disk blocks
int memory[SIZE] = {0};

// ---------- Sequential Allocation ----------
void sequentialAllocation() {
    int start, length, i, flag = 0;

    printf("\n[Sequential Allocation]");
    printf("\nEnter starting block and length of file: ");
    scanf("%d %d", &start, &length);

    if (start + length > SIZE) {
        printf("File exceeds memory limit.\n");
        return;
    }

    for (i = start; i < start + length; i++) {
        if (memory[i] == 1) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        for (i = start; i < start + length; i++) {
            memory[i] = 1;
        }
        printf("File allocated from block %d to %d\n", start, start + length - 1);
    } else {
        printf("Blocks not free. Allocation failed.\n");
    }
}

// ---------- Indexed Allocation ----------
void indexedAllocation() {
    int indexBlock, n, blocks[SIZE], i;

    printf("\n[Indexed Allocation]");
    printf("\nEnter index block: ");
    scanf("%d", &indexBlock);

    if (memory[indexBlock] == 1) {
        printf("Index block already allocated.\n");
        return;
    }

    printf("Enter number of blocks needed: ");
    scanf("%d", &n);

    printf("Enter block numbers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &blocks[i]);
        if (memory[blocks[i]] == 1 || blocks[i] >= SIZE) {
            printf("Block %d not free or invalid. Allocation failed.\n", blocks[i]);
            return;
        }
    }

    memory[indexBlock] = 1;
    for (i = 0; i < n; i++) {
        memory[blocks[i]] = 1;
    }

    printf("File allocated with index block %d -> ", indexBlock);
    for (i = 0; i < n; i++) {
        printf("%d ", blocks[i]);
    }
    printf("\n");
}

// ---------- Linked Allocation ----------
struct Node {
    int block;
    struct Node *next;
};

void linkedAllocation() {
    int start, n, i, block;
    struct Node *head = NULL, *temp = NULL, *newNode;

    printf("\n[Linked Allocation]");
    printf("\nEnter number of blocks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter block %d: ", i + 1);
        scanf("%d", &block);

        if (block >= SIZE || memory[block] == 1) {
            printf("Block %d not free or invalid. Allocation failed.\n", block);
            return;
        }

        memory[block] = 1;
        newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->block = block;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else
            temp->next = newNode;

        temp = newNode;
    }

    printf("File allocated in blocks: ");
    temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->block);
        temp = temp->next;
    }
    printf("NULL\n");
}

// ---------- Main Function ----------
int main() {
    int choice;

    while (1) {
        printf("\n\nFile Allocation Methods");
        printf("\n1. Sequential Allocation");
        printf("\n2. Indexed Allocation");
        printf("\n3. Linked Allocation");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sequentialAllocation();
                break;
            case 2:
                indexedAllocation();
                break;
            case 3:
                linkedAllocation();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
