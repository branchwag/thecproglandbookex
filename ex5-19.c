//mod undcl so it doesn't add redundant parentheses to declarations
//uindcl converts C declarations to word description

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXLEN 1000

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void undcl(void);
void dirdcl(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXLEN];

int main() {
  while (gettoken() != EOF) {
    strcpy(datatype, token);
    out[0] = '\0';
    undcl();
    if (out[0] != '\0') {
        printf("%s: %s\n", name, out);
    }
  }
  return 0;
}

int gettoken(void) {
  int c;
  char *p = token;

  while ((c = getchar()) == ' ' || c == '\t') {
    ;
  }

  if (c == '(') {
    if ((c = getchar()) == ')') {
        strcpy(token, "()");
        return tokentype = PARENS;
    } else {
        ungetc(c, stdin); 
        return tokentype = '(';
    }
  }

  if (c == '[') {
    return tokentype = '[';
  }

  if (isalpha(c)) {
    *p++ = c;
    while (isalnum(c = getchar())) {
        *p++ = c;
    }

    *p = '\0';
    ungetc(c, stdin);
    return tokentype = NAME;
  }

    if (c == EOF) {
      return EOF;
    }

    return tokentype = c;
}

void undcl(void) {
  int ns = 0;
  while (gettoken() == '*') {
    ns++;
  }
  dirdcl();
  while (ns-- > 0) {
    strcat(out, " pointer to");
  }
}

void dirdcl(void) {
  int type; 
  if (tokentype == '(') {
    undcl();
    if (tokentype != ')') {
      printf("error: missing )\n");
    }
  } else if (tokentype == NAME) {
      strcpy(name, token);
  } else {
      printf("error: expected name or (dirdcl)\n");
  }

  while ((type = gettoken()) == '[') {
      if (gettoken() != ']') {
          printf("error: missing ]\n");
      } 
      strcat(out, " array of");
  }

  if (tokentype == '(') {
    strcat (out, " function returning");
  }
}

