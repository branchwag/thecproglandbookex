#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXVARS 1000
#define MAXNAME 100

typedef struct {
    char name[MAXNAME];
} VarName;

VarName varNames[MAXVARS];
int varCount = 0;
int prefixLength = 0;

void extractVarNames(FILE *file);
int isVariableChar(char c);
void printGroupedVarNames();

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <prefix_length> <source_file.c>\n", argv[0]);
        return 1;
    }

    prefixLength = atoi(argv[1]);
    if (prefixLength < 1 || prefixLength > MAXNAME) {
        fprintf(stderr, "Prefix length must be between 1 and %d\n", MAXNAME);
        return 1;
    }

    FILE *file = fopen(argv[2], "r"); // Adjust this to your source file name
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    extractVarNames(file);
    fclose(file);

    printGroupedVarNames();
    return 0;
}

void extractVarNames(FILE *file) {
    char c;
    char varName[MAXNAME];
    int inString = 0;
    int inComment = 0;
    int i = 0;

    while ((c = fgetc(file)) != EOF) {
        if (c == '"') {
            inString = !inString; //changes val to 1
            continue;
        }

        if (c == '/' && !inString) {
            if ((c = fgetc(file)) == '*') {
                inComment = 1; // Start of block comment
            } else if (c == '/') {
                while ((c = fgetc(file)) != '\n' && c != EOF);
                continue; // Skip line comment
            } else {
                ungetc(c, file);
            }
        }

        if (inComment) {
            if (c == '*') {
                if ((c = fgetc(file)) == '/') {
                    inComment = 0; // End of block comment
                }
            }
            continue; // Skip everything inside comments
        }

        if (isVariableChar(c)) {
            varName[i++] = c;
        } else {
            if (i > 0) {
                varName[i] = '\0';
                if (varCount < MAXVARS) {
                    strcpy(varNames[varCount++].name, varName);
                }
                i = 0; // Reset for the next variable
            }
        }
    }
}

int isVariableChar(char c) {
    return isalnum(c) || c == '_'; // Valid variable characters
}

void printGroupedVarNames() {
    char prefixes[MAXVARS][MAXNAME];
    int counts[MAXVARS] = {0};
    int totalGroups = 0;

    for (int i = 0; i < varCount; i++) {
        char prefix[MAXNAME];
        strncpy(prefix, varNames[i].name, prefixLength);
        prefix[prefixLength] = '\0';

        int found = 0;
        for (int j = 0; j < totalGroups; j++) {
            if (strcmp(prefixes[j], prefix) == 0) {
                counts[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(prefixes[totalGroups], prefix);
            counts[totalGroups] = 1;
            totalGroups++;
        }
    }

    for (int i = 0; i < totalGroups; i++) {
        if (counts[i] > 1) {
            printf("%s: %d\n", prefixes[i], counts[i]);
        }
    }
}

