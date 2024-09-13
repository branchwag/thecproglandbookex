#include <stdio.h>

#define MAXVAL 100
#define VAR_COUNT 26

static double variables[VAR_COUNT] = {0};

static double val[MAXVAL];
static int sp = 0;         // Next free position in stack

void push(double f) {
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void print_top(void) {
    if (sp > 0) {
        printf("\t%.8g\n", val[sp-1]);
    } else {
        printf("error: stack empty\n");
    }
}

void duplicate(void) {
    if (sp > 0) {
        push(val[sp-1]);
    } else {
        printf("error: stack empty\n");
    }
}

void swap(void) {
    if (sp > 1) {
        double temp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = temp;
    } else {
        printf("error: not enough elements to swap\n");
    }
}

void clear_stack(void) {
    sp = 0;
}

void set_variable(char var, double value) {
    if (var >= 'A' && var <= 'Z') {
        variables[var - 'A'] = value;
    } else {
        printf("error: invalid variable %c\n", var);
    }
}

double get_variable(char var) {
    if (var >= 'A' && var <= 'Z') {
        return variables[var - 'A'];
    } else {
        printf("error: invalid variable %c\n", var);
        return 0.0;
    }
}

