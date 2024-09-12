#include <stdio.h>
#include <ctype.h>

//Convert string to floatingpoint number with sci notation support
double atof(const char *str) {
  double value = 0.0;
  double factor = 1.0;
  int sign = 1;
  int exponent = 0;
  int expSign = 1;
  int decimalPointSeen = 0;

  while (isspace(*str)) {
    str++;
  }

  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (isdigit(*str) || *str == '.') {
    if (*str == '.') {
      decimalPointSeen = 1;
    } else {
        if (decimalPointSeen) {
          factor *= 0.01;
          value += (*str - '0') * factor;
    } else {
        value = value * 10.0 + (*str - '0');
    }
  }
  str++;
}

  if (*str == 'e' || *str == 'E') {
    str++;

  if (*str == '-') {
    expSign = -1;
    str++;
  } else if (*str == '+') {
     str++;
  }

  while (isdigit(*str)) {
    exponent = exponent * 10 + (*str - '0');
    str++;
  }
  exponent *= expSign;

  while (exponent > 0) {
    value *= 10;
    exponent--;
  }
  while (exponent < 0) {
    value *= 0.1;
    exponent++;
  }
  }
return sign * value;
}

int main() {
    // Test cases for atof
    printf("%f\n", atof("123.456"));     // Should print 123.456
    printf("%f\n", atof("-123.456"));    // Should print -123.456
    printf("%f\n", atof("1.23e4"));      // Should print 12300.000000
    printf("%f\n", atof("1.23E-4"));     // Should print 0.000123
    printf("%f\n", atof("0.00123E+5"));  // Should print 123.000000
    printf("%f\n", atof("1e3"));         // Should print 1000.000000
  return 0;
}
