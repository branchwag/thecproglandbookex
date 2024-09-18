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

int next_tab_stop(int col) {
  for (int i = 0; i < ntabs; ++i) {
       if (tabstops[i] > col) {
          return tabstops[i];
       }
  }
  return col + 8; //defaulting to 8 spaces if no tab stop found
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
  detab(stdin, stdout);
  return 0;
}
