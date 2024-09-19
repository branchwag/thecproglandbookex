//dcl program reads and interprets var declartions. Processes string input to parse var types and names
//enter int a; program parses int and a
//if you enter int a alone, program should complain about missing semi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

int gettoken(char s[], char *input);
void dcl(char *input);
void dirdcl(void);
void recover(char *input);

int main(void) {
  char input[MAXTOKEN];

  while (1) {
    printf("Enter a declaration (or Ctrl + D to exit): ");
    if (fgets(input, MAXTOKEN, stdin) == NULL) break; 
    recover(input);
  }
  return 0;
}

void recover(char *input) {
  if (strchr(input, ';') == NULL) {
    fprintf(stderr, "Error: Missing semicolon.\n");
    return;
   }
  dcl(input);
}

void dcl(char *input) {
  char token[MAXTOKEN];
  int type;

  while ((type = gettoken(token, input)) != EOF) {
    if (type == 'a') {
      printf("Token: %s\n", token);
    } else {
      fprintf(stderr, "Error: Invalid token encountered: %s\n", token);
      return;
    }
  }
}

int gettoken(char s[], char *input) {
  while (*input && isspace(*input)) input++;
  if (*input == '\0') return EOF;
  if (isalnum(*input)) {
    char *p = s;
    while (isalnum(*input)) {
      *p++ = *input++;
    }
    *p = '\0';
    return 'a';
  }

  return 0;
}

