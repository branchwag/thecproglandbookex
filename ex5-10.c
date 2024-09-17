//reverse polish expression from the command line where each operator or operand is a separate argument.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

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

void eval(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
       char *arg = argv[i];
       if (isdigit(arg[0])) {
         push(atof(arg));
        } else {
         double op2 = pop();
         double op1 = pop();
         switch (arg[0]) {
           case '+': push(op1 + op2); break;
           case '*': push(op1 * op2); break;
           case '-': push(op1 - op2); break;
           case '/':
              if (op2 != 0.0) {
                push(op1 / op2);
               } else {
                printf("error: zero divisor\n");
              } 
              break;
            default:
                printf("error: unknown operator %s\n", arg);
                return;
         }
       }
  }

if (sp == 1) {
  printf("Result: %g\n", pop());
  } else {
  printf("error: too many operands\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <expression>\n", argv[0]);
    return 1;
  }
  eval(argc, argv);
  return 0;
}
