//create private version of scanf like minprintf
#include <stdio.h>
#include <stdarg.h>

void minscanf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  while (*fmt) {
    if (*fmt == '%') {
        fmt++;
        switch (*fmt) {
          case 'd': {
            int *ip = va_arg(ap, int*);
            scanf("%d", ip);
            break;
          }
          case 'f': {
              float *fp = va_arg(ap, float*);
              scanf("%f", fp);
              break;
          }
          case 's': {
            char *sp = va_arg(ap, char*);
            scanf("%s", sp);
            break;
          }
          default:
            break;
          }
        }
        fmt++;
    }
  va_end(ap);
}

int main() {
  int i;
  float f;
  char s[100];

  printf("Enter an int, a float, and string: ");
  minscanf("%d %f %s", &i, &f, s);
  
  printf("You entered: %d, %f, %s\n", i, f, s);
  return 0;
}
