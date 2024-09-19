#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 1000
#define MAXFIELDS 10
#define MAXLINE 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int n);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *, int, int), int field, int numeric);
int numcmp(char *, char *);
int strcmp_fields(char *s1, char *s2, int field, int numeric);
int compare_wrapper(void *s1, void *s2, int field, int numeric);

int main(int argc, char *argv[]) {
    int nlines;
    int field = 0;
    int numeric = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-f", 2) == 0) {
            field = atoi(argv[i] + 2) - 1; // Convert to 0-based index
        }
        if (strcmp(argv[i], "-n") == 0) {
            numeric = 1; // Enable numeric sorting
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        my_qsort((void **) lineptr, 0, nlines - 1, compare_wrapper, field, numeric);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines) {
    char *line = NULL;  // Pointer to hold the line
    size_t len = 0;     // Length of the line
    int nlines = 0;

    while ((getline(&line, &len, stdin)) != -1) {
        if (nlines >= maxlines || (lineptr[nlines] = strdup(line)) == NULL) {
            free(line); // Free memory if allocation failed
            return -1;  // Error
        }
        nlines++;
    }
    free(line); // Free memory allocated by getline
    return nlines;
}

void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *, int, int), int field, int numeric) {
    int i, last;

    if (left >= right) return; // Base case

    last = left;
    for (i = left + 1; i <= right; i++) {
        if (comp(lineptr[i], lineptr[left], field, numeric) < 0) {
            last++;
            char *temp = lineptr[last];
            lineptr[last] = lineptr[i];
            lineptr[i] = temp;
        }
    }
    // Swap pivot
    char *temp = lineptr[left];
    lineptr[left] = lineptr[last];
    lineptr[last] = temp;

    my_qsort(lineptr, left, last - 1, comp, field, numeric);
    my_qsort(lineptr, last + 1, right, comp, field, numeric);
}

int compare_wrapper(void *s1, void *s2, int field, int numeric) {
    return strcmp_fields((char *)s1, (char *)s2, field, numeric);
}

int strcmp_fields(char *s1, char *s2, int field, int numeric) {
    char *field1 = strtok(s1, " ");
    char *field2 = strtok(s2, " ");
    for (int i = 0; i < field; i++) {
        if (field1 != NULL) field1 = strtok(NULL, " ");
        if (field2 != NULL) field2 = strtok(NULL, " ");
    }

    if (numeric) {
        return numcmp(field1, field2);
    } else {
        return strcmp(field1, field2);
    }
}

int numcmp(char *s1, char *s2) {
    double num1 = atof(s1);
    double num2 = atof(s2);

    if (num1 < num2) {
        return -1;
    } else if (num1 > num2) {
        return 1;
    } else {
        return 0;
    }
}

void writelines(char *lineptr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s", lineptr[i]);
    }
}

