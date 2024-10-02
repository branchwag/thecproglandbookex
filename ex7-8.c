//write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file
#include <stdio.h>
#include <stdlib.h>

#define PAGE_WIDTH 72
#define PAGE_HEIGHT 60

void print_page_header(const char *filename, int page_number) {
    printf("\n\n");
    printf("%*s\n", PAGE_WIDTH, " "); // Centering the title
    printf("%*s\n", PAGE_WIDTH, "=====================");
    printf("%*s\n", PAGE_WIDTH, filename);
    printf("%*s\n", PAGE_WIDTH, "=====================");
    printf("Page %d\n\n", page_number);
}

void print_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file: %s\n", filename);
    return;
  }

  char line[1024];
  int page_number = 1;
  int line_count = 0;

  print_page_header(filename, page_number);

  while (fgets(line, sizeof(line), file) != NULL) {
    printf("%s", line);
    line_count++;
    
    if (line_count >= PAGE_HEIGHT) {
      page_number++;
      line_count = 0;
      print_page_header(filename, page_number);
    }
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
      fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
      return 1;
    }

    for (int i = 1; i < argc; i++) {
         print_file(argv[i]);
    }

    return 0;
}
