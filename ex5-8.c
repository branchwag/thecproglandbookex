#include <stdio.h>

static char daytab[2][13] = {
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
  int i, leap;
  leap = year%4 == 0 && year%100 != 0 || year%400==0;
  for (i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

int is_valid_date(int year, int month, int day) {
  int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  if (month < 1 || month > 12) return 0;
  if (day < 1 || day > daytab[leap][month]) return 0;
  return 1;
}

int main() {
  int year, month, day, yearday;
  int pmonth, pday;

    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month: ");
    scanf("%d", &month);
    printf("Enter day: ");
    scanf("%d", &day);

    if (!is_valid_date(year, month, day)) {
      printf("Error: invalid date entered.\n");
      return 1;
    }

    yearday = day_of_year(year, month, day);
    printf("Day of year: %d\n", yearday);

    month_day(year, yearday, &pmonth, &pday);
    printf("Month: %d, Day: %d\n", pmonth, pday);

    return 0;
}
