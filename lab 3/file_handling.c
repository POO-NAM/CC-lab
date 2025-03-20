#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createAndWriteFile() {
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    char input[100];
    printf("Enter content to write into the file: ");
    fgets(input, sizeof(input), stdin);
    fprintf(file, "%s", input);
    fclose(file);
    printf("File created and data written successfully.\n");
}

void readFile() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error reading file");
        return;
    }
    char line[100];
    printf("Contents of the file:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void appendToFile() {
    FILE *file = fopen("example.txt", "a");
    if (file == NULL) {
        perror("Error appending to file");
        return;
    }
    char input[100];
    printf("Enter content to append: ");
    fgets(input, sizeof(input), stdin);
    fprintf(file, "%s", input);
    fclose(file);
    printf("Data appended successfully.\n");
}

void deleteFile() {
    if (remove("example.txt") == 0) {
        printf("File deleted successfully.\n");
    } else {
        perror("Error deleting the file");
    }
}

void searchWordInFile() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error reading file");
        return;
    }
    char word[50], buffer[100];
    int count = 0;
    printf("Enter the word to search: ");
    scanf("%s", word);
    while (fscanf(file, "%s", buffer) != EOF) {
        if (strcmp(buffer, word) == 0) {
            count++;
        }
    }
    fclose(file);
    printf("The word '%s' occurred %d times.\n", word, count);
}

int main() {
    int choice;
    do {
        printf("\nFile Handling Menu:\n");
        printf("1. Create and Write File\n");
        printf("2. Read File\n");
        printf("3. Append to File\n");
        printf("4. Delete File\n");
        printf("5. Search for Word\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear the buffer
        switch (choice) {
            case 1: createAndWriteFile(); break;
            case 2: readFile(); break;
            case 3: appendToFile(); break;
            case 4: deleteFile(); break;
            case 5: searchWordInFile(); break;
            case 6: printf("Exiting program.\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
    return 0;
}


