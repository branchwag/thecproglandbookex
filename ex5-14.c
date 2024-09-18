#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 1000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_custom(void *v[], int left, int right, int (*comp)(void *, void *, int), int reverse);
int numcmp(char *, char *);
int mystrcmp(char *, char *);
int reverse_order(int reverse, int comparison);

int main(int argc, char *argv[]) {
    int nlines;     
    int numeric = 0;  // 1 if sorting numerically
    int reverse = 0;  // 1 if sorting in reverse order

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            numeric = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        }
    }

    // Read lines from input
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        // Sort the lines
        qsort_custom((void **)lineptr, 0, nlines - 1, numeric ? (int (*)(void *, void *, int))numcmp : (int (*)(void *, void *, int))mystrcmp, reverse);
        // Write the sorted lines
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char line[MAXLEN]; // buffer for reading lines

    nlines = 0;
    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0'; // remove newline
        }
        if (nlines >= maxlines || (lineptr[nlines] = malloc(len)) == NULL) {
            return -1; // too many lines or memory allocation error
        } else {
            strcpy(lineptr[nlines++], line);
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

void qsort_custom(void *v[], int left, int right, int (*comp)(void *, void *, int), int reverse) {
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right) {
        return; // do nothing if array is small
    }
    swap(v, left, (left + right) / 2); // move pivot to start
    last = left; // partitioning
    for (i = left + 1; i <= right; i++) {
        if (reverse_order(reverse, comp(v[i], v[left], reverse)) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last); // restore pivot
    qsort_custom(v, left, last - 1, comp, reverse);
    qsort_custom(v, last + 1, right, comp, reverse);
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s1, char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}

int mystrcmp(char *s1, char *s2) {
    return strcmp(s1, s2);
}

int reverse_order(int reverse, int comparison) {
    return reverse ? -comparison : comparison;
}
