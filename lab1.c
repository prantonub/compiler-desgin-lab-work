#include <stdio.h>
#include <stdlib.h>  // Needed for system()

int main() {
    FILE *file;

    // Create or overwrite lab1.txt
    file = fopen("lab1.txt", "w");

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    fprintf(file, "This is Lab 1's content.\nWelcome to file handling in C!\n");
    fclose(file);  // Always close the file

    printf("File written successfully.\n");

    // ✅ Open the file in Notepad (Windows only)
    system("notepad lab1.txt");

    return 0;
}
