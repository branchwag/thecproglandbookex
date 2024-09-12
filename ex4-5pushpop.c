#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Add the commands to print the top elements of the stack without popping, to
//duplicate it, and to swap the top two elements. Add a command to clear the stack.

#define MAXVAL 100
static int sp = 0; //next free stack pos
static double val[MAXVAL]; //value stack

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
  }

double pop(void) {
    if (sp > 0)
      return val[--sp];
    else {
      printf("error: stack empty\n");
      return 0.0;
    }
}

//print top element without popping
void print_top(void) {
  if (sp > 0)
    printf("Top element: %.8g\n", val[sp - 1]);
  else
    printf("error: stack empty\n");
}

//dupe top element of stack
void duplicate(void) {
  if (sp > 0) {
    double top = val[sp - 1];
    push(top);
  } else {
      printf("error: stack empty\n");
    }
}

//swap top two elements
void swap(void) {
  if (sp > 1) {
    double temp1 = val[sp -1];
    double temp2 = val[sp - 2];
    val[sp - 1] = temp2;
    val[sp - 2] = temp1;
  } else { 
      printf("error: not enough elements to swap\n");
  }
}

void clear_stack(void) {
  sp = 0;
}


