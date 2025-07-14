#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '<' || ch == '>' || ch == '%' ||
            ch == '!' || ch == '&' || ch == '|');
}
int isSpecialSymbol(char ch) {
    return (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' || ch == '[' || ch == ']');
}
int main() {
    char ch, buffer[15];
    FILE *fpInput, *fpOutput;
    int j = 0;

    fpInput = fopen("lab1.txt", "r");
    fpOutput = fopen("output.txt", "w");

    if (fpInput == NULL || fpOutput == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(fpInput)) != EOF) {
        if (isalnum(ch)) {
            buffer[j++] = ch;
            if (j >= 14) {
                buffer[j] = '\0';
                j = 0;
                if (isKeyword(buffer))
                    fprintf(fpOutput, "%s is keyword\n", buffer);
                else
                    fprintf(fpOutput, "%s is identifier\n", buffer);
            }
        } else {
            if (j != 0) {
                buffer[j] = '\0';
                j = 0;
                if (isKeyword(buffer))
                    fprintf(fpOutput, "%s is keyword\n", buffer);
                else
                    fprintf(fpOutput, "%s is identifier\n", buffer);
            }
            if (isOperator(ch)) {
                char next = fgetc(fpInput);
                if ((ch == '=' && next == '=') ||
                    (ch == '!' && next == '=') ||
                    (ch == '<' && next == '=') ||
                    (ch == '>' && next == '=')) {
                    fprintf(fpOutput, "%c%c is operator\n", ch, next);
                } else {
                    ungetc(next, fpInput);
                    fprintf(fpOutput, "%c is operator\n", ch);
                }
            } else if (isSpecialSymbol(ch)) {
                fprintf(fpOutput, "%c is special symbol\n", ch);
            }
        }
    }
    if (j != 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            fprintf(fpOutput, "%s is keyword\n", buffer);
        else
            fprintf(fpOutput, "%s is identifier\n", buffer);
    }
    fclose(fpInput);
    fclose(fpOutput);
    printf("Output run successfully. Please check output.txt.\n");
    system("notepad output.txt");
    return 0;
}
