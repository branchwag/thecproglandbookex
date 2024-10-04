#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char buffer[1024];

  if (argc == 1) {
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
      printf("%s", buffer);
    }
  } else {
      for (int i = 1; i < argc; i++) {
           fp = fopen(argv[i], "r");
           if (fp == NULL) {
              perror("fopen");
              return 1;
           }
      while (fgets(buffer, sizeof(buffer), fp) != NULL) {
           printf("%s", buffer);
           }
        fclose(fp);
      }
    }
    return 0;
}
