//Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.
//dcl parses declarations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXQUALIFIERS 10
#define MAXOUTPUT 200

enum { NAME, PARENS, BRACKETS, CONST, VOLATILE };

int gettoken(void);
void dcl(void);
void dcl_line(void);
void process_function_arguments(char *output);
void add_qualifier(char *output, const char *qualifier);
void finalize_type(char *output);

char token[MAXTOKEN];
char output[MAXOUTPUT];
int token_type;
int ns; // num of pointer asterisks
char qualifiers[MAXQUALIFIERS][MAXTOKEN];
int qualifier_count;

int main(void) {
  while(1) {
    printf("Enter a declaration: ");
    dcl_line();
    printf("Output: %s\n", output);
    output[0] = '\0';
  } 
  return 0;
}

void dcl_line(void) {
  qualifier_count = 0;
  output[0] = '\0';
  ns = 0;

  while ((token_type = gettoken()) == CONST || token_type == VOLATILE) {
    add_qualifier(output, token);
  }

if (token_type == NAME) {
  strcat(output, token);
  } else {
    printf("Error: Expected a type name\n");
    return;
  }

while (token_type == PARENS || token_type == BRACKETS || token_type == '*') {
    if (token_type == '*') {
      ns++;
      strcat(output, " pointer to ");
    } else if (token_type == PARENS) {
       strcat(output, " function returning ");
       process_function_arguments(output);
    } else if (token_type == BRACKETS) {
        strcat(output, " array of ");
    }
    token_type = gettoken();
  }

  for (int i = 0; i < ns; i++) {
     strcat(output, " pointer to");
  }

  finalize_type(output);
}

void process_function_arguments(char *output) {
    strcat(output, " (");
    while (gettoken() != ')') {
        if (token_type == NAME) {
            strcat(output, token);
            token_type = gettoken();
            if (token_type == ',') {
                strcat(output, ", ");
            } else if (token_type != ')') {
                printf("Error: Expected ',' or ')'\n");
                return;
            }
        } else {
            printf("Error: Expected a parameter type\n");
            return;
        }
    }
    strcat(output, ")");
}

void add_qualifier(char *output, const char *qualifier) {
    strcat(output, qualifier);
    strcat(output, " ");
}

void finalize_type(char *output) {
    char temp[MAXOUTPUT];
    strcpy(temp, output);
    output[0] = '\0';

    char *token = strtok(temp, " ");
    while (token != NULL) {
        if (strcmp(token, "") != 0) {
            strcat(output, token);
            strcat(output, " ");
        }
        token = strtok(NULL, " ");
    }

    if (output[strlen(output) - 1] == ' ') {
        output[strlen(output) - 1] = '\0';
    }
}

int gettoken(void) {
    int c;

    while ((c = getchar()) == ' ' || c == '\t'); // Skip whitespace

    if (c == EOF) return EOF;

    if (isalpha(c)) {
        ungetc(c, stdin);
        scanf("%s", token);
        if (strcmp(token, "const") == 0) return CONST;
        if (strcmp(token, "volatile") == 0) return VOLATILE;
        return NAME;
    }

    if (c == '(') {
        token[0] = c;
        token[1] = '\0';
        return PARENS;
    }

    if (c == ')') {
        token[0] = c;
        token[1] = '\0';
        return PARENS;
    }

    if (c == '[') {
        token[0] = c;
        token[1] = '\0';
        return BRACKETS;
    }

    if (c == ']') {
        token[0] = c;
        token[1] = '\0';
        return BRACKETS;
    }

    if (c == '*') {
        token[0] = c;
        token[1] = '\0';
        return '*';
    }

    return c; 
}
