#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char str[], int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    start++;
    end--;
  }
}

void itoa_recursive(int num, char str[], int *index) {
  if (num == 0) {
    return;
  }

  int digit = num % 10;
  num /= 10;

  itoa_recursive(num, str, index);

  str[*index] = digit + '0';
  (*index)++;
}

char* itoa(int num) {
  if (num == 0) {
    char* str = (char*)malloc(2);
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  char temp[100];
  int index = 0;
  int is_negative = 0;

  if(num < 0) {
    is_negative = 1;
    num = -num;
  }

  itoa_recursive(num, temp, &index);

  temp[index] = '\0';

  if (is_negative) {
  temp[index] = '-';
  temp[index + 1] = '\0';
  index++;
  }

  reverse(temp, index);

  char* result = (char*)malloc(index + 1);
  strcpy(result, temp);

  return result;
}

int main() {
  int number = -1234;
  char* str = itoa(number);
  printf("The string representation is %s:\n", str);
  free(str);
  return 0;
}

