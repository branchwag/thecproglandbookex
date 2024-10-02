//write a program to compare two files, printing first line where they differ
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);\
    return 1;
  }

  FILE *file1 = fopen(argv[1], "r");
  FILE *file2 = fopen(argv[2], "r");

  if (file1 == NULL) {
    fprintf(stderr, "Error opening file 1.\n");
    return 1;
  }

  if (file2 == NULL) {
    fprintf(stderr, "Error opening file 2.\n");
    return 1;
  }

  char line1[MAXLINE];
  char line2[MAXLINE];
  int lineNumber = 0;

  while (fgets(line1, MAXLINE, file1) != NULL && fgets(line2, MAXLINE, file2) != NULL) {
    lineNumber++;
    if (strcmp(line1, line2) != 0) {
      printf("Difference found at line %d:\n", lineNumber);
      printf("File 1: %s", line1);
      printf("File 2: %s", line2);
      fclose(file1);
      fclose(file2);
      return 0;
    }
  }

  if (fgets(line1, MAXLINE, file1) != NULL) {
    printf("File 1 has extra line %d: %s", lineNumber + 1, line1);
  } else if (fgets(line2, MAXLINE, file2) != NULL) {
      printf("File 2 has extra line %d: %s", lineNumber + 1, line2);
  }

  fclose(file1);
  fclose(file2);
  printf("File are identical\n");
  return 0;
}
  
