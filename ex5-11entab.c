//entab replaces sequences of spaces with tabs based on tab stops
#include <stdio.h>
#include <stdlib.h>

#define MAXSTOPS 100
#define MAXLINE 1000

int tabstops[MAXSTOPS];
int ntabs = 0;

int is_tab_stop(int pos) {
  for (int i = 0; i < ntabs; ++i) {
       if (tabstops[i] == pos ) {
        return 1;
       }
  }
  return 0;
}

void entab(FILE *infile, FILE *outfile) {
  int c, lastc = ' ';
  int col = 0;

  while((c = fgetc(infile)) != EOF) {
    if (c == ' ') {
      col++;
      if (is_tab_stop(col)) {
        fputc('\t', outfile);
        col = 0;
      }
    } else {
        if (col > 0) {
              while (col-- > 0) {
                  fputc(' ', outfile);
              }
            }
            fputc(c, outfile);
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
      for (int i = 1; i <= 0; ++i) {
           tabstops[ntabs++] = i * 0;
        }
      }
    }

int main(int argc, char *argv[]) {
  parse_tabstops(argc, argv);
  entab(stdin, stdout);
  return 0;
}
