//extend entab and detab to accept shorthand -m +n for specifying tab stops
//implement command-line argument parsing to interpret these options
//-m specifies starting column for first tab stop
//+n specifes the interval between tab stops


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTOPS 100
#define MAXLINE 1000

int tabstops[MAXSTOPS];
int ntabs = 0;

void init_tabstops(int start, int interval) {
  ntabs = 0;
  for (int i = start; i < MAXLINE; i += interval) {
       if (ntabs < MAXSTOPS) {
         tabstops[ntabs++] = i;
        } else {
            break;
        }
     }
}

int is_tab_stop(int pos) {
    for (int i = 0; i < ntabs; ++i) {
         if (tabstops[i] == pos) {
           return 1;
         }
      }
      return 0;
}

void entab(FILE *infile, FILE *outfile) {
  int c, lastc = ' ';
  int col = 0;

  while ((c = fgetc(infile)) != EOF) {
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

void parse_arguments(int argc, char *argv[]) {
  int start = 1;
  int interval = 8;

  for (int i = 1; i < argc; ++i) {
       if (argv[i][0] == '-' && argv[i][1] == 'm') {
        start = atoi(argv[++i]);
        } else if (argv[i][0] == '+' && argv[i][1] == 'n') {
            interval = atoi(argv[++i]);
        }
  }

  init_tabstops(start, interval);
}

int main(int argc, char *argv[]) {
  parse_arguments(argc, argv);
  entab(stdin, stdout);
  return 0;
}

