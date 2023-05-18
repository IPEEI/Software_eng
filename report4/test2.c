#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *file = fopen("Alice_in_Wonderland.txt", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        printf("%s\n",word);
    }
    fclose(file);
    return 0;
}