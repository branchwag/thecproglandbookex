//do _flushbuf, fflush, fclose
//_flushbuf - writes contents of output buffer to file
//fflush - flushes output buffer of a stream, ensuring that all data is written to the file
//fclose - closes file associated with a stream, ensuring that any buffered data is written and the file descriptor is freed
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int my_flushbuf(FILE *fp) {
  if (fp == NULL) {
    return EOF;
  }
  if (fflush(fp) !=0) {
    return EOF;
  }
  return 0;
}

int my_fflush(FILE *fp) {
  if (fp == NULL) {
    return my_flushbuf(stdout);
  }
  return my_flushbuf(fp);
}

int my_fclose(FILE *fp) {
  if (fp == NULL) {
    return EOF;
  }

  if (my_fflush(fp) == EOF) {
    return EOF;
  }

  if (fclose(fp) != 0) {
    return EOF;
  }

  return 0;
}

int main() {
  FILE *f = stdout;

  fputs("Hello, world!\n", f);

  if (my_fflush(f) == EOF) {
    perror("Failed to flush buffer");
    return 1;
  }

  if (my_fclose(f) == EOF) {
    perror("Failed to close stream");
    return 1;
  }

  return 0;
}
