
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000
#define MAXLINES 1000

int readlines(char *lineptr[], int maxlines, char *buffer, int buffer_size);

int readlines(char *lineptr[], int maxlines, char *buffer, int buffer_size) {
    int len, nlines = 0;
    size_t len_buffer = buffer_size;
    char *line_start = buffer;
    char *current_pos = buffer;

    while ((len = getline(&current_pos, &len_buffer, stdin)) > 0) {
        if (nlines >= maxlines) {
            return -1; // Too many lines
        }

        // Remove newline character if present
        if (len > 0 && current_pos[len-1] == '\n') {
            current_pos[len-1] = '\0';
            len--;
        }

        // Store the pointer to the start of the line in lineptr
        lineptr[nlines++] = current_pos;
        
        // Move the buffer pointer forward
        current_pos += len + 1;
        len_buffer = buffer_size - (current_pos - buffer);

        if (len_buffer <= 0) {
            return -1; // Buffer too small
        }
    }

    return nlines;
}

int main(void) {
    char buffer[MAXLEN * MAXLINES]; // Single buffer for all lines
    char *lineptr[MAXLINES];
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES, buffer, sizeof(buffer))) >= 0) {
        for (int i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
        return 0;
    } else {
        printf("Error: input too large or buffer overflow\n");
        return 1;
    }
}
