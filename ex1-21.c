#include <stdio.h>

#define TAB_STOP 8

void replace_blanks_with_tabs_and_spaces(FILE *input, FILE *output) {
  int c;
  int column = 0;

  while ((c = fgetc(input)) != EOF) {
    if (c == ' ') {
      int num_spaces = 0;
      while (c == ' ') {
        num_spaces++;
        c = fgetc(input);
    }

    int tabs = num_spaces / TAB_STOP;
    int spaces = num_spaces % TAB_STOP;

    for (int i = 0; i < tabs; i++) { 
         fputc('\t', output);
         column += TAB_STOP;
      }
    for (int i = 0; i < spaces; i++) {
      fputc(' ', output);
      column++;
    }
    if (c != EOF) {
      fputc(c, output);
      column++;
      if (c == '\n') {
        column = 0;
      }
    }
} else { 
    fputc(c, output);
    column++;
    if (c == '\n') {
      column = 0;
     }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s inputfile outputfile\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "r"); 
  if (input == NULL) {
    perror("Error opening input file");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (output == NULL) {
    perror("Error opening output file");
    fclose(input);
    return 1;
  }

  replace_blanks_with_tabs_and_spaces(input, output);

  fclose(input);
  fclose(output);

  return 0;
}

