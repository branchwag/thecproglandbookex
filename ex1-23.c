#include <stdio.h>
#include <stdbool.h>

void remove_comments(FILE *input, FILE *output);
bool is_in_string_literal(const char *text, int pos);
bool is_in_char_constant(const char *text, int pos);

void remove_comments(FILE *input, FILE *output) {
  int c, prev_char = 0;
  bool in_string = false;
  bool in_char = false;

  while ((c = fgetc(input)) != EOF) {
    if(in_string) {
      if (c == '"' && prev_char != '\\') {
        in_string = false;
    }
    fputc(c, output);
    } else if (in_char) {
      if (c == '\'' && prev_char != '\\') {
        in_char = false;
      }
      fputc(c, output);
    } else {
      if (c == '/' && prev_char == '/') {
        while (c != '\n' && c != EOF) {
          c = fgetc(input);
        }
        fputc('\n', output);
      } else if (c == '/' && prev_char == '*') {
        while (c != EOF) {
          if (c == '*' && (c = fgetc(input)) == '/') {
            break;
          }
          c = fgetc(input);
        }
    } else {
      if (c == '"') {
        in_string = true;
      } else if (c == '\'') {
          in_char = true;
      } 
      fputc(c, output);
      }
    }
    prev_char = c;
  }
}

int main (int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }

  FILE *input = fopen(argv[1], "r");
  if (!input) {
    perror("error opening input file");
    return 1;
  }

  FILE *output = fopen(argv[2], "w");
  if (!output) {
    perror("Error opening output file");
    fclose(input);
    return 1;
  }

  remove_comments(input, output);

  fclose(input);
  fclose(output);

  return 0;
}



