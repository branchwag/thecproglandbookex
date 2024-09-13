#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NUMBER '0'
#define FUNC 'f'
#define VAR 'v'

int getop(char s[], char **ptr) {
    int i = 0;
    char c;

    while ((c = **ptr) == ' ' || c == '\t') {
        (*ptr)++;
    }

    if (c == '\0') {
        return '\0';
    }

    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '\n') {
        (*ptr)++;
        return c;
    }

    if (isalpha(c)) {
        s[i++] = c;
        (*ptr)++;
        while (isalpha(c = **ptr)) {
            s[i++] = c;
            (*ptr)++;
        }
        s[i] = '\0';
        return FUNC;
    }

    if (isdigit(c) || c == '.') {
        while (isdigit(s[i++] = c)) {
            c = *(*ptr)++;
        }
        if (c == '.') {
            s[i++] = c;
            while (isdigit(c = *(*ptr)++)) {
                s[i++] = c;
            }
        }
        s[i] = '\0';
        return NUMBER;
    }

    if (c == '=') {
        s[i++] = c;
        (*ptr)++;
        if (isupper(**ptr)) {
            s[i++] = **ptr;
            (*ptr)++;
        }
        s[i] = '\0';
        return VAR;
    }

    return c;
}

