#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    // If the file is unreadable/no file
    if (!file) {
        perror ("Unable to open file");
        return 1;
    }

    int ch, lines = 0, words = 0, characters = 0;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        characters++;
        if(ch == '\n') lines++;
        if(isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    
    fclose(file);

    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);
    printf("Lines: %d\n", lines);

    return 0;
}

int count_word_occurrences(const char *filename, const char *word) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("unable to open file");
        return 0;
    }   

    int count = 0;
    char buffer[1000];
    size_t len = strlen(word);

    while (fscanf(file, "%999s", buffer) == 1) {
        if (strcasecmp(buffer, word) == 0) {
            count++;
        }
    }

    fclose(file);
    return count;
}

int main() {
    char filename[100];
    char word[100];
    int file_opened = 0;



    // Prompt user for the filename until a valid file is opened
    while (!file_opened) {
        printf("Enter the filename: ");
        scanf("%99s", filename);
        if (count_file_contents(filename) == 0) {
            file_opened = 1;
        } else {
            printf("File not found or unable to open. Please try again.\n");
        }
    }

    //clear the input buffer
    while (getchar() != '\n');

    printf("Enter a word to search (or press Enter to skip): ");
    if (fgets(word, sizeof(word), stdin)) {
        size_t len =strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0';
        }
    }
    
    if (strlen(word) == 0) {
        printf("no word selected\n");
    } else {
        int occurrences = count_word_occurrences(filename, word);
        printf("the word '%s' occurs %d times in the file.\n", word, occurrences);
    }

    return 0;
}