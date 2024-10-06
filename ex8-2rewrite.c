//rewrite fopen and _fillbuf with fields instead of explicit bit operations

//fopen opens file and associates with file stream
//func sig FILE *fopen(const char *filename, const char *mode);
//allocs mem, opens file, sets flags (mode), allocs buffer, return pointer

//_fillbuff reads data from file into internal buffer
//checks if buffer full, reads data from file, handles EOF and errors, updates FILE structure, return char

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

struct my_iobuf {
    int cnt;
    char *ptr;
    char *base;
    bool read : 1;
    bool write : 1;
    bool eof : 1;
    bool err : 1;
    int fd;
};

typedef struct my_iobuf MyFILE;

MyFILE *my_fopen(const char *filename, const char *mode) {
  MyFILE *fp;
  int fd;

  if ((fp = malloc(sizeof(MyFILE))) == NULL)
    return NULL;

  if (*mode == 'r') {
    fd = open(filename, O_RDONLY);
    fp->read = true;
    fp->write = false;
  } else if (*mode == 'w') {
      fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666); 
      fp->read = false;
      fp->write = true;
  } else {
      free(fp);
      return NULL;
  }

  if (fd < 0) {
    free(fp);
    return NULL;
  }

  fp->fd = fd;
  fp->eof = false;
  fp->err = false;
  fp->cnt = 0;
  fp->base = malloc(BUFSIZE);
  fp->ptr = fp->base;

  return fp;
}

int my_fillbuf(MyFILE *fp) {
  int n;

  if (!fp->read || fp ->cnt > 0)
    return EOF;

  n = read(fp->fd, fp->base, BUFSIZE);
  if (n < 0) {
    fp->err = true;
    return EOF;
  }

  if (n == 0) {
    fp->eof = true;
    return EOF;
  }

  fp->cnt = n;
  fp->ptr = fp->base;
  return (unsigned char) *fp->ptr++;
}

int main() {
  MyFILE *fp = my_fopen("test.txt", "r");
  if (fp == NULL) {
    perror("Failed to open file");
    return 1;
  }

  int c;
  while ((c = my_fillbuf(fp)) != EOF) {
    putchar(c);
  }

  if (fp->err)
    printf("\nError reading file\n");

  if (fp->eof)
    printf("\nEnd of file reached\n");

  free(fp->base);
  free(fp);

  return 0;
}
