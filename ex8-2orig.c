#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
};

typedef struct _iobuf FILE;

#define READ 0x01
#define WRITE 0x02
#define EOF 0x04
#define ERR 0x08

FILE *fopen(const char *filename, const char *mode) {
  FILE *fp;
  int fd;

  if((fp = malloc(sizeof(FILE))) == NULL)
    return NULL;

  if (*mode == 'r') {
    fd = open(filename, O_RDONLY);
    fp->flag = READ;
  } else if (*mode == 'w') {
      fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
      fp->flag = WRITE;
  } else {
      free(fp);
      return NULL;
  }

  if (fd < 0) {
    free(fp);
    return NULL;
  }

  fp->fd = fd;
  fp->flag &= ~(EOF | ERR);
  fp->cnt = 0;
  fp->base = malloc(BUFSIZE);
  fp->ptr = fp->base;

  return fp;
}

int _fillbuf(FILE *fp) {
    int n;
    
    if ((fp->flag & READ) == 0 || fp->cnt > 0)
      return EOF;

    n = read(fp->fd, fp->base, BUFSIZE);
    if (n < 0) {
      fp->flag |= ERR;
      return EOF;
    }

    if (n == 0) {
      fp->flag |= EOF;
      return EOF;
    }

    fp->cnt = n;
    fp->ptr = fp->base;
    return (unsigned char) *fp->ptr++;
}

int main() {
    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL) {
      perror("Failed to open file");
      return 1;
    }

    int c;
    while ((c = _fillbuf(fp)) != EOF) {
      putchar(c);
    }

    if (fp->flag & ERR)
      printf("\nError reading file\n");

    if (fp->flag & EOF)
      printf("\nEnd of file reached\n");

    free(fp->base);
    free(fp);

    return 0;
}
