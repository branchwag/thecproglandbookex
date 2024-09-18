#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 1000
#define MAXLEN 1000

char *lineptr[MAXLINES];
int fold_case = 0;
int dir_order = 0;

int readlines(char *lineptr[], int nlines);
int get_line(char *line, int max);
void writelines(char *lineptr[], int nlines);
int compare(const void *a, const void *b);

int get_line(char *line, int max) {
  int c, i;

  for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
       line[i] = c;
  }
  if (c == '\n') {
      line[i++] = c;
  }
  line[i] = '\0';
  return i;
}

int compare (const void *a, const void *b) {
  char *s1 = *(char **)a;
  char *s2 = *(char **)b;
  char c1, c2;
  int i = 0, j = 0;

  while (1) {
    if (dir_order) {
            while (s1[i] && !isalnum((unsigned char)s1[i])) i++;
            while (s2[j] && !isalnum((unsigned char)s2[j])) j++;
        }

        c1 = s1[i];
        c2 = s2[j];

        if (fold_case) {
            c1 = tolower((unsigned char)c1);
            c2 = tolower((unsigned char)c2);
        }

        if (c1 != c2) {
            return c1 - c2;
        }

        if (c1 == '\0' || c2 == '\0') {
            return strlen(s1 + i) - strlen(s2 + j);
        }

        i++;
        j++;
    }
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
        free(lineptr[i]);
    }
}

int main(int argc, char *argv[]) {
    int nlines;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            fold_case = 1; 
        } else if (strcmp(argv[i], "-d") == 0) {
            dir_order = 1;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, nlines, sizeof(char *), compare);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}
