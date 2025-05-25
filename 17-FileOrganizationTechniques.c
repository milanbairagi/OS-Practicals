#include <stdio.h>
#include <string.h>

#define MAX_FILES 5
#define MAX_USERS 3

// Structure for Single Level Directory
struct SingleLevel {
    char files[MAX_FILES][20];
    int file_count;
};

// Structure for Two Level Directory
struct TwoLevel {
    char user[MAX_USERS][20];
    struct SingleLevel user_files[MAX_USERS];
};

// Structure for Hierarchical Directory (Simple version with one level of subdirectories)
struct Hierarchical {
    char main_directory[20];
    struct SingleLevel subdirectories[MAX_USERS];
};

// Function to display files in single level directory
void singleLevelDirectory(struct SingleLevel *dir) {
    printf("\nSingle Level Directory:\n");
    for (int i = 0; i < dir->file_count; i++) {
        printf("%d. %s\n", i + 1, dir->files[i]);
    }
}

// Function to display files in two-level directory
void twoLevelDirectory(struct TwoLevel *dir) {
    printf("\nTwo Level Directory:\n");
    for (int i = 0; i < MAX_USERS; i++) {
        if (strlen(dir->user[i]) > 0) {
            printf("User: %s\n", dir->user[i]);
            for (int j = 0; j < dir->user_files[i].file_count; j++) {
                printf("\t%d. %s\n", j + 1, dir->user_files[i].files[j]);
            }
        }
    }
}

// Function to display files in hierarchical directory
void hierarchicalDirectory(struct Hierarchical *dir) {
    printf("\nHierarchical Directory:\n");
    printf("Main Directory: %s\n", dir->main_directory);
    for (int i = 0; i < MAX_USERS; i++) {
        if (strlen(dir->subdirectories[i].files[0]) > 0) {
            printf("\tSubdirectory: %d\n", i + 1);
            for (int j = 0; j < dir->subdirectories[i].file_count; j++) {
                printf("\t\t%d. %s\n", j + 1, dir->subdirectories[i].files[j]);
            }
        }
    }
}

int main() {
    // Single Level Directory Example
    struct SingleLevel single_dir = {{"file1.txt", "file2.txt", "file3.txt"}, 3};
    
    // Two Level Directory Example
    struct TwoLevel two_level_dir = {
        {"user1", "user2", "user3"},
        {
            {{"file1.txt", "file2.txt"}, 2},
            {{"file3.txt", "file4.txt"}, 2},
            {{"file5.txt"}, 1}
        }
    };
    
    // Hierarchical Directory Example
    struct Hierarchical hierarchical_dir = {
        "MainDir", 
        {
            {{"file1.txt", "file2.txt"}, 2},
            {{"file3.txt", "file4.txt"}, 2},
            {{"file5.txt"}, 1}
        }
    };

    // Display all directory structures
    singleLevelDirectory(&single_dir);
    twoLevelDirectory(&two_level_dir);
    hierarchicalDirectory(&hierarchical_dir);

    return 0;
}
