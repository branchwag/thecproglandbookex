#include <stdio.h> 

int getch(void);
void ungetch(int);

int main() {
  int c;

  c = getch();
  printf("Read character: %c\n", c);

  ungetch(c);

  c = getch(); 
  printf("Read character again: %c\n", c);

  return 0;
}
