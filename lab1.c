#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check whether a given word is a C keyword
int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    // Loop through all keywords and compare with buffer
    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1; // It's a keyword
        }
    }
    return 0; // Not a keyword
}

int main() {
    char ch, buffer[15]; // buffer to store each word
    FILE *fp, *out;      // file pointers
    int j = 0;           // buffer index

    // Open input file for reading
    fp = fopen("lab1.txt", "r");
    if (fp == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open output file for writing
    out = fopen("output.txt", "w");
    if (out == NULL) {
        printf("Error opening output file.\n");
        fclose(fp);
        return 1;
    }

    // Read character by character until end of file
    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch)) {
            // If character is alphanumeric, store it in buffer
            buffer[j++] = ch;
        }
        // If separator is encountered and buffer has content
        else if ((ch == ' ' || ch == '\n' || ch == '\t' || ch == ',' || ch == ';') && j != 0) {
            buffer[j] = '\0'; // Null-terminate the word
            j = 0; // Reset buffer index

            // Check if buffer is a keyword or identifier
            if (isKeyword(buffer))
                fprintf(out, "%s is keyword\n", buffer);
            else
                fprintf(out, "%s is identifier\n", buffer);
        }
    }

    // Handle last word if file ends without space
    if (j != 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            fprintf(out, "%s is keyword\n", buffer);
        else
            fprintf(out, "%s is identifier\n", buffer);
    }

    // Close both files
    fclose(fp);
    fclose(out);

    // Open the output file in Notepad (only works on Windows)
    system("notepad output.txt");

    return 0;
}
