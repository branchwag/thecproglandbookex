#include <stdio.h>
#include <stdlib.h> // for atof
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100   // max size of operand or operator
#define NUMBER '0'  // signal that a number was found
#define PRINT 'p'   // command to print the top element
#define DUPLICATE 'd' // command to duplicate the top element
#define SWAP 's'    // command to swap the top two elements
#define CLEAR 'c'   // command to clear the stack
#define FUNC 'f'
#define VAR 'v'

#define VAR_COUNT 26

int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void duplicate(void);
void swap(void);
void clear_stack(void);
void set_variable(char, double);
double get_variable(char);
void print_recent(double);

double recent_value = 0.0;

int main() {
    int type;
    double op1, op2;
    char s[MAXOP];

    double variables[VAR_COUNT] = {0};

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                op1 = pop();
                if (op2 != 0.0)
                    push((int)op1 % (int)op2);
                else
                    printf("error: zero divisor\n");
                break;
            case PRINT:   // Print top element
                print_top();
                break;
            case DUPLICATE: // Duplicate top element
                duplicate();
                break;
            case SWAP:   // Swap top two elements
                swap();
                break;
            case CLEAR:  // Clear stack
                clear_stack();
                break;
            case FUNC:
              if (strcmp(s, "sin") == 0) {
                    push(sin(pop()));
                } else if (strcmp(s, "exp") == 0) {
                    push(exp(pop()));
                } else if (strcmp(s, "pow") == 0) {
                    op2 = pop();
                    op1 = pop();
                    push(pow(op1, op2));
                } else {
                    printf("error: unknown function %s\n", s);
                }
                break;
            case VAR:
              if (strlen(s) == 2 && s[0] == '=') {
                    set_variable(s[1], pop());
              } else if (strlen(s) == 1 && isupper(s[0])) {
                    push(get_variable(s[0]));
                } else {
                    printf("error: invalid variable command %s\n", s);
                }
                break;
            case '\n':
                recent_value = pop();
                print_recent(recent_value);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

void print_recent(double value) {
    printf("\t%.8g\n", value);
}

