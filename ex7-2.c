//display input. print non-graphic characters in octal. hexi according to local custom. break long text lines.
#include <stdio.h>

#define MAXLINE 80

void print_char(char c) {
  //octal for non-graphic
  if (c < 32 || c >= 127) {
    printf("\\%03o", (unsigned char)c);
  } else {
      putchar(c); //graphic chars just normally print
  }
}

int main() {
  int c; 
  int line_length = 0;

  while ((c = getchar()) != EOF) {
    if (line_length >= MAXLINE) {
      putchar('\n');
      line_length = 0;
    }

    print_char(c);
    line_length++;
  }

  return 0; 
}


