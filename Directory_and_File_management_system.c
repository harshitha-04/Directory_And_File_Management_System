#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File ADT
typedef struct File {
    char name[50];
    char content[1000];
    struct File* left;  // For Binary Search Tree
    struct File* right;
} File;

// Function to create a new file
File* createFile(const char* name, const char* content) {
    File* newFile = malloc(sizeof(File));
    if (newFile == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newFile->name, name);
    strcpy(newFile->content, content);
    newFile->left = NULL;
    newFile->right = NULL;
    return newFile;
}

// Function to display files in a directory (BST)
void displayFiles(File* file) {
    if (file != NULL) {
        displayFiles(file->left);
        printf("File: %s\n", file->name);
        displayFiles(file->right);
    }
}

// Directory ADT with Linked List
typedef struct Directory {
    char name[50];
    struct Directory* prev;  // Pointer to the previous directory
    struct Directory* next;  // Pointer to the next directory
    File* files;             // Binary Search Tree of Files
} Directory;

// Function to create a new directory
Directory* createDirectory(const char* name) {
    Directory* newDirectory = malloc(sizeof(Directory));
    if (newDirectory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newDirectory->name, name);
    newDirectory->prev = NULL;
    newDirectory->next = NULL;
    newDirectory->files = NULL;
    return newDirectory;
}

// Function to add a file to a directory
void addFileToDirectory(Directory* currentDir, File* newFile) {
    if (currentDir->files == NULL) {
        currentDir->files = newFile;
    } else {
        File* currentFile = currentDir->files;
        File* parent = NULL;

        while (1) {
            int cmp = strcmp(newFile->name, currentFile->name);

            if (cmp == 0) {
                printf("File with the same name already exists in the current directory. Choose a different name.\n");
                free(newFile);
                return;
            } else if (cmp < 0) {
                if (currentFile->left == NULL) {
                    currentFile->left = newFile;
                    break;
                }
                parent = currentFile;
                currentFile = currentFile->left;
            } else {
                if (currentFile->right == NULL) {
                    currentFile->right = newFile;
                    break;
                }
                parent = currentFile;
                currentFile = currentFile->right;
            }
        }
    }
}

// Function to display the contents of a directory and its files
void displayDirectoryContents(Directory* currentDir) {
    if (currentDir == NULL) return;
    Directory* tempDir = currentDir;

    // Display directories in forward direction
    while (tempDir != NULL) {
        printf("Directory: %s\n", tempDir->name);
        displayFiles(tempDir->files);
        tempDir = tempDir->next;
    }

    // Display directories in backward direction
    tempDir = currentDir->prev;
    while (tempDir != NULL) {
        printf("Directory: %s\n", tempDir->name);
        displayFiles(tempDir->files);
        tempDir = tempDir->prev;
    }
}

// Function to delete a file from a directory
void deleteFileFromDirectory(Directory* currentDir, const char* fileName) {
    File* currentFile = currentDir->files;
    File* parent = NULL;

    while (currentFile != NULL) {
        int cmp = strcmp(fileName, currentFile->name);

        if (cmp < 0) {
            parent = currentFile;
            currentFile = currentFile->left;
        } else if (cmp > 0) {
            parent = currentFile;
            currentFile = currentFile->right;
        } else {
            // File found, perform deletion
            if (currentFile->left == NULL && currentFile->right == NULL) {
                // Case 1: No child
                if (parent != NULL) {
                    if (parent->left == currentFile) {
                        parent->left = NULL;
                    } else {
                        parent->right = NULL;
                    }
                } else {
                    currentDir->files = NULL;
                }
                free(currentFile);
            } else if (currentFile->left == NULL) {
                // Case 2: One child (right)
                if (parent != NULL) {
                    if (parent->left == currentFile) {
                        parent->left = currentFile->right;
                    } else {
                        parent->right = currentFile->right;
                    }
                } else {
                    currentDir->files = currentFile->right;
                }
                free(currentFile);
            } else if (currentFile->right == NULL) {
                // Case 2: One child (left)
                if (parent != NULL) {
                    if (parent->left == currentFile) {
                        parent->left = currentFile->left;
                    } else {
                        parent->right = currentFile->left;
                    }
                } else {
                    currentDir->files = currentFile->left;
                }
                free(currentFile);
            } else {
                // Case 3: Two children
                File* minRight = currentFile->right;
                parent = currentFile;

                // Find the leftmost node in the right subtree
                while (minRight->left != NULL) {
                    parent = minRight;
                    minRight = minRight->left;
                }

                // Copy the values of the leftmost node to the current node
                strcpy(currentFile->name, minRight->name);
                strcpy(currentFile->content, minRight->content);

                // Remove the leftmost node
                if (parent->left == minRight) {
                    parent->left = minRight->right;
                } else {
                    parent->right = minRight->right;
                }
                free(minRight);
            }
            return;
        }
    }
    printf("File not found.\n");
}

// Function to delete a directory and its contents
void deleteDirectory(Directory* currentDir) {
    if (currentDir == NULL) return;
    File* currentFile = currentDir->files;

    // Free files in the current directory
    while (currentFile != NULL) {
        File* temp = currentFile;
        currentFile = currentFile->right;
        free(temp);
    }

    // Recursively delete subdirectories
    deleteDirectory(currentDir->next);

    // Adjust pointers in the linked list
    if (currentDir->prev != NULL) {
        currentDir->prev->next = currentDir->next;
    }
    if (currentDir->next != NULL) {
        currentDir->next->prev = currentDir->prev;
    }

    // Free the current directory
    free(currentDir);
}

// Function to search for a file in the directory and its subdirectories
void searchFile(Directory* currentDir, const char* fileName) {
    if (currentDir == NULL) return;
    File* currentFile = currentDir->files;

    // Search for the file in the current directory
    while (currentFile != NULL) {
        if (strcmp(fileName, currentFile->name) == 0) {
            printf("File found in directory '%s':\n", currentDir->name);
            printf("Name: %s\n", currentFile->name);
            printf("Content: %s\n", currentFile->content);
            return;  // Exit function after finding the file
        }
        currentFile = currentFile->right;
    }

    // Recursively search in subdirectories
    searchFile(currentDir->next, fileName);
}

// Function to edit the content of a file
void editFile(File* file, const char* content) {
    if (file != NULL) {
        strcpy(file->content, content);
    }
}

int main() {
    Directory* root = createDirectory("root");
    Directory* currentDir = root;
    char command[50];
    char name[50];
    char content[1000];

    // Main loop for user commands
    while (1) {
        printf("\nCurrent Directory: %s\n", currentDir->name);
        printf("Enter command (createDir, createFile, listDir, changeDir, deleteFile, deleteDir, searchFile, editFile, quit): ");
        scanf("%s", command);

        // Process user command
        if (strcmp(command, "createDir") == 0) {
            printf("Enter directory name: ");
            scanf("%s", name);
            // No need for createDirCheck as it was not defined
            // You can directly call createDirectory
            Directory* newDir = createDirectory(name);
            currentDir->next = newDir;
            newDir->prev = currentDir;
            currentDir = newDir;
        } else if (strcmp(command, "createFile") == 0) {
            printf("Enter file name: ");
            scanf("%s", name);
            printf("Enter file content: ");
            getchar();  // Consume newline character left by previous scanf
            fgets(content, sizeof(content), stdin);
            File* newFile = createFile(name, content);
            addFileToDirectory(currentDir, newFile);
        } else if (strcmp(command, "listDir") == 0) {
            displayDirectoryContents(root);
        } else if (strcmp(command, "changeDir") == 0) {
            printf("Enter directory name: ");
            scanf("%s", name);
            Directory* tempDir = root;
            while (tempDir != NULL) {
                if (strcmp(tempDir->name, name) == 0) {
                    currentDir = tempDir;
                    break;
                }
                tempDir = tempDir->next;
            }
            if (tempDir == NULL) {
                printf("Directory not found.\n");
            }
        } else if (strcmp(command, "deleteFile") == 0) {
            printf("Enter file name: ");
            scanf("%s", name);
            deleteFileFromDirectory(currentDir, name);
        } else if (strcmp(command, "deleteDir") == 0) {
            deleteDirectory(currentDir);
            currentDir = currentDir->prev;
        } else if (strcmp(command, "searchFile") == 0) {
            printf("Enter file name: ");
            scanf("%s", name);
            searchFile(currentDir, name);
        } else if (strcmp(command, "editFile") == 0) {
            printf("Enter file name: ");
            scanf("%s", name);
            File* currentFile = currentDir->files;
            while (currentFile != NULL) {
                if (strcmp(name, currentFile->name) == 0) {
                    printf("Enter new content: ");
                    getchar();  // Consume newline character left by previous scanf
                    fgets(content, sizeof(content), stdin);
                    editFile(currentFile, content);
                    printf("File content updated successfully.\n");
                    break;  // Removed the 'return' statement
                }
                currentFile = currentFile->right;
            }
            if (currentFile == NULL) {
                printf("File not found.\n");
            }
        } else if (strcmp(command, "quit") == 0) {
            break;
        } else {
            printf("Invalid command.\n");
        }
    }

    // Free allocated memory before exiting
    deleteDirectory(root);

    return 0;
}
