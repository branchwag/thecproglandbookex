#include <stdio.h>
#include <ctype.h>

int htoi(const char *s) {
  int result = 0;
  int value;

//check for optional '0x' or '0x' prefix
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
    s += 2;
  }

while (*s) {
  if (isdigit(*s)) {
    value = *s - '0';
  } else if (islower(*s)) {
      value = *s - 'a' + 10;
  } else if (isupper(*s)) {
      value = *s - 'A' + 10;
  } else {
    return -1;
  }

  result = (result << 4) | value;
  s++;
 }
 return result;
}

int main() {
    const char *hexStr1 = "0x1a3F";
    const char *hexStr2 = "FF";
    const char *hexStr3 = "0Xabc";
    
    printf("Hex string \"%s\" converts to %d\n", hexStr1, htoi(hexStr1));
    printf("Hex string \"%s\" converts to %d\n", hexStr2, htoi(hexStr2));
    printf("Hex string \"%s\" converts to %d\n", hexStr3, htoi(hexStr3));

    return 0;
}

