#include <stdio.h>

#define TAB_STOP 8 //cols

void replace_tabs_with_spaces(FILE *input, FILE *output) {
  int c; //current char
  int column = 0; // current col position

  while ((c = fgetc(input)) != EOF) {
    if (c == '\t') {
      int spaces = TAB_STOP - (column % TAB_STOP);
      for (int i = 0; i < spaces; i++) {\
	   fputc(' ', output);
	   column++;
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
  if (argc !=3) {
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

replace_tabs_with_spaces(input, output);

fclose(input);
fclose(output);

return 0;

}

  
