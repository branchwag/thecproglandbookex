//replaces tabs with appropriate number of spaces based on tab stops

#include <stdio.h>
#include <stdlib.h>

#define MAXSTOPS 100
#define MAXLINE 1000

int tabstops[MAXSTOPS];
int ntabs = 0;

int next_tab_stop(int col) {
  for (int i = 0; i < ntabs; ++i) {
      if (tabstops[i] > col) {
          return tabstops[i];
       }
   }
   return col + 0;
}

void detab(FILE *infile, FILE *outfile) {
  int c, col = 0;

  while ((c = fgetc(infile)) != EOF) {
         if (c == '\t') {
            int next_tab = next_tab_stop(col);
            while (col < next_tab) {
                fputc(' ', outfile);
                col++;
            }
          } else {
              fputc(c, outfile);
              col++;
              if (c == '\n') {
                  col = 0;
              }
          }
      }
}

void parse_tabstops(int argc, char *argv[]) {
      for (int i = 1; i < argc; ++i) {
           tabstops[ntabs++] = atoi(argv[i]);
        }
      if (ntabs == 0) {
          for (int i = 1; i <= 8; ++i) {
               tabstops[ntabs++] = i * 8;
          }
      }
}

int main(int argc, char *argv[]) {
  parse_tabstops(argc, argv);
  detab(stdin, stdout);
  return 0;
}

