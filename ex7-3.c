//revise minprintf to handle more of the other facilities of printf

#include <stdio.h>
#include <stdarg.h>

void minprintf(const char *fmt, ...);

int main() {
    minprintf("Hello, %s!\n", "world");
    minprintf("Integer: %d\n", 42);
    minprintf("Floating point: %.2f\n", 3.14159);
    minprintf("Hexadecimal: %x\n", 255);
    minprintf("Padding: |%5d|\n", 42); // width
    minprintf("Precision: |%.3f|\n", 3.14159); // precision
    return 0;
}

void minprintf(const char *fmt, ...) {
  va_list ap;
  char *p, *sval;
  int ival;
  double dval;

  va_start(ap, fmt);

  for (p = (char *)fmt; *p; p++) {
       if (*p != '%') {
          putchar(*p);
          continue;
       }
       p++;

      int width = 0;
      while (*p >= '0' && *p <= '9') {
          width = width * 10 + (*p - '0');
          p++;
      }

      int precision = -1;
      if (*p == '.') {
        p++;
        precision = 0;
        while (*p >= '0' && *p <= '9') {
          precision = precision * 10 + (*p - '0');
          p++;
        }
    }

       switch (*p) {
           case 'd':
                ival = va_arg(ap, int);
                if (width > 0) {
                    printf("%*d", width, ival);
                } else {
                    printf("%d", ival);
                }
                break;
            case 'f':
                dval = va_arg(ap, double);
                if (precision >= 0) {
                    if (width > 0) {
                        printf("%*.*f", width, precision, dval);
                    } else {
                        printf("%.2f", dval); // Default precision if not specified
                    }
                } else {
                    printf("%f", dval);
                }
                break;
            case 's':
                sval = va_arg(ap, char *);
                if (width > 0) {
                    printf("%*s", width, sval);
                } else {
                    printf("%s", sval);
                }
                break;
            case 'x':
                ival = va_arg(ap, int);
                printf("%*x", width, ival);
                break;
          default:
            putchar(*p);
            break;
       }
  }
  va_end(ap);
}

