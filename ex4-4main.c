#include <stdio.h>
#include <stdlib.h> // for atof

#define MAXOP 100   // max size of operand or operator
#define NUMBER '0'  // signal that a number was found
#define PRINT 'p'   // command to print the top element
#define DUPLICATE 'd' // command to duplicate the top element
#define SWAP 's'    // command to swap the top two elements
#define CLEAR 'c'   // command to clear the stack

int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void duplicate(void);
void swap(void);
void clear_stack(void);

int main() {
    int type;
    double op1, op2;
    char s[MAXOP];

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
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

