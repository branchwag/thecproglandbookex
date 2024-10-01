//rewrite ch4 calc to use scanf or sscanf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXVAL 100
#define MAXLINE 100

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

int main() {
  char line[MAXLINE];
  char *token;
  double op2;

  printf("Enter postfix expression (end with newline):\n");
  if (fgets(line, MAXLINE, stdin) == NULL) {
    return 1;
   }

  token = strtok(line, " \t\n");

  while (token != NULL) {
      if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        push(atof(token));
      } else {
          switch (token[0]) {
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
              if (op2 != 0.0) {
                push(pop() / op2);
              } else {
                printf("error: zero divisor\n");
              }
              break;
            default:
              printf("error: unknown commands %s\n", token);
              break;
        }
    }
    token = strtok(NULL, " \t\n");
  }

  printf("Result: %.8g\n", pop());
  return 0;
}


