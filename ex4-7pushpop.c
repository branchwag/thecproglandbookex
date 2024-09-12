#include <stdio.h>

#define VAR_COUNT 26 // Number of variables (A-Z)

static double stack[VAR_COUNT];
static int sp = 0;

static double variables[VAR_COUNT] = {0}; // Variables 'A' to 'Z'

void push(double f) {
    if (sp < VAR_COUNT)
        stack[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void print_top(void) {
    if (sp > 0)
        printf("\t%.8g\n", stack[sp - 1]);
    else
        printf("error: stack empty\n");
}

void duplicate(void) {
    if (sp > 0)
        push(stack[sp - 1]);
    else
        printf("error: stack empty\n");
}

void swap(void) {
    if (sp >= 2) {
        double temp = stack[sp - 1];
        stack[sp - 1] = stack[sp - 2];
        stack[sp - 2] = temp;
    } else
        printf("error: not enough elements to swap\n");
}

void clear_stack(void) {
    sp = 0;
}

void set_variable(char var, double value) {
    if (var >= 'A' && var <= 'Z') {
        variables[var - 'A'] = value;
    } else {
        printf("error: invalid variable name %c\n", var);
    }
}

double get_variable(char var) {
    if (var >= 'A' && var <= 'Z') {
        return variables[var - 'A'];
    } else {
        printf("error: invalid variable name %c\n", var);
        return 0.0;
    }
}

