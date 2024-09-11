#include <stdio.h> 

#define MAXLINE 1000

int my_getline(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main() {
  char line[MAXLINE];
  int found = 0;

  while (my_getline(line, MAXLINE) > 0)
    if (strrindex(line, pattern) >= 0) {
      printf("%s", line);
      found++;
    }
  return found;
}


int my_getline(char s[], int lim) {
  int c, i;
  i = 0;
  while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

int strrindex(char s[], char t[]) {
  int i, j, k;
  int s_len = 0;
  int t_len = 0;

  while (s[s_len] != '\0') s_len++;
  while (t[t_len] != '\0') t_len++;

  if (t_len > s_len) return -1; 

  for (i = s_len - t_len; i >= 0; i--) {
       for (j=i, k=0; k < t_len && s[j] == t[k]; j++, k++)
          ;
       if (k == t_len)
         return i;
  }
  return -1;
}
