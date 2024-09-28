//convert upper case to lower or lower to upper, depending on the name it is invoked with, as found in argv[0]

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int to_lower = 0;
  if (strstr(argv[0], "lower") != NULL) {
      to_lower = 1;
  } else if (strstr(argv[0], "upper") != NULL) {
      to_lower = 0;
  } else {
      fprintf(stderr, "Usage: %s lower|upper\n", argv[0]);
      return 1;
  }

  int c;
  while ((c = getchar()) != EOF) {
    if (to_lower) {
        putchar(tolower(c));
    } else {
        putchar(toupper(c));
    }
  }

  return 0;
}
