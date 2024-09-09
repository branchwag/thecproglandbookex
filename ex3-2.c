#include <stdio.h>

void escape(char *s, const char *t) {
    while (*t) {
        switch (*t) {
            case '\n':
                *s++ = '\\';
                *s++ = 'n';
                break;
            case '\t':
                *s++ = '\\';
                *s++ = 't';
                break;
            case '\\':
                *s++ = '\\';
                *s++ = '\\';
                break;
            default:
                *s++ = *t;
                break;
        }
        t++;
    }
    *s = '\0';  // Null-terminate the result string
}

void unescape(char *s, const char *t) {
    while (*t) {
        if (*t == '\\') {
            t++;
            switch (*t) {
                case 'n':
                    *s++ = '\n';
                    break;
                case 't':
                    *s++ = '\t';
                    break;
                case '\\':
                    *s++ = '\\';
                    break;
                default:
                    *s++ = '\\';
                    *s++ = *t;
                    break;
            }
        } else {
            *s++ = *t;
        }
        t++;
    }
    *s = '\0';  // Null-terminate the result string
}

int main() {
  char escaped[100];
  char unescaped[100];

  const char *original = "Hello\tWorld!\nThis is a test.";

  escape(escaped, original);
  printf("Escaped: %s\n", escaped);

  unescape(unescaped, escaped);
  printf("Unescaped: %s\n", unescaped);

  return 0;
}




