//mod the pattern finding program from ch5 to take input from set of named files, or, if no files are named as args, from standard input
//should file name be printed when a matching line is found?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

void find_pattern_in_file(FILE *fp, const char *filename, const char *pattern) {
  char line[MAXLINE];
  int line_number = 0;

  while (fgets(line, MAXLINE, fp) != NULL) {
    line_number++;
    if (strstr(line, pattern) != NULL) {
      printf("%s:%d: %s", filename, line_number, line);
    }
  }
}

int main(int argc, char *argv[]) {
    const char *pattern = "pattern";
    
    if (argc < 2) {
      printf("Usage: %s pattern [file1 file2 ...]\n", argv[0]);
      return 1;
    }

    pattern = argv[1];

    if (argc == 2) {
      find_pattern_in_file(stdin, "stdin", pattern);
    } else {
      for (int i = 2; i < argc; i++) {
          FILE *fp = fopen(argv[i], "r");
          if (fp == NULL) {
            fprintf(stderr, "Could not open file: %s\n", argv[i]);
            continue;
           }
           find_pattern_in_file(fp, argv[i], pattern);
           fclose(fp);
    }
  }

return 0;
}


