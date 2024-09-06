#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STACK_SIZE 1000

typedef struct {
    char stack[MAX_STACK_SIZE];
    int top;
} Stack;

void push(Stack *s, char c) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->stack[++(s->top)] = c;
    } else {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

char pop(Stack *s) {
    if (s->top >= 0) {
        return s->stack[(s->top)--];
    } else {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

bool is_empty(Stack *s) {
    return s->top == -1;
}

bool is_balanced(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

bool check_balance(const char *code) {
    Stack s;
    s.top = -1;
    char c;

    while ((c = *code++)) {
        if (c == '(' || c == '[' || c == '{') {
            push(&s, c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (is_empty(&s) || !is_balanced(pop(&s), c)) {
                return false;
            }
        }
    }
    return is_empty(&s);
}

bool check_quotes(const char *code) {
    bool in_single_quote = false;
    bool in_double_quote = false;
    char c, prev_c = '\0';

    while ((c = *code++)) {
        if (c == '\'') {
            if (in_double_quote) continue;
            if (prev_c == '\\') continue;
            in_single_quote = !in_single_quote;
        } else if (c == '"') {
            if (in_single_quote) continue;
            if (prev_c == '\\') continue;
            in_double_quote = !in_double_quote;
        }
        prev_c = c;
    }
    return !in_single_quote && !in_double_quote;
}

void remove_comments(char *code) {
    char *src = code, *dst = code;
    bool in_single_comment = false;
    bool in_multi_comment = false;

    while (*src) {
        if (in_single_comment) {
            if (*src == '\n') {
                in_single_comment = false;
                *dst++ = *src++;
            } else {
                src++;
            }
        } else if (in_multi_comment) {
            if (*src == '*' && *(src + 1) == '/') {
                in_multi_comment = false;
                src += 2;
            } else {
                src++;
            }
        } else {
            if (*src == '/' && *(src + 1) == '/') {
                in_single_comment = true;
                src += 2;
            } else if (*src == '/' && *(src + 1) == '*') {
                in_multi_comment = true;
                src += 2;
            } else {
                *dst++ = *src++;
            }
        }
    }
    *dst = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *code = malloc(file_size + 1);
    if (!code) {
        perror("malloc");
        fclose(file);
        return EXIT_FAILURE;
    }

    fread(code, 1, file_size, file);
    fclose(file);
    code[file_size] = '\0';

    remove_comments(code);

    if (check_balance(code) && check_quotes(code)) {
        printf("No syntax errors detected\n");
    } else {
        printf("Error: Unbalanced parentheses, brackets, braces, or quotes\n");
    }

    free(code);
    return EXIT_SUCCESS;
}

