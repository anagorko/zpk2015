#include <iostream>
using namespace std;
int main() {
int X, Y, a, b, c, d, e, year, day, month;
cin >> year;
  if (year <= 1899)
  {
    X = 23;
    Y = 4;
  }
  else if (year <= 2099)
  {
    X = 24;
    Y = 5;
  }
  else if (year <= 2199)
  {
    X = 24;
    Y = 6;
  }
  else 
  {
    X = 25;
    Y = 0;
  }
    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = (a * 19 + A) % 30;
    e = (2 * b + 4 * c + 6 * d + B) % 7;
    day = (22 + d + e) % 31;
    
  if (22 + d + e <= 31)
     mies = 3;
  else
    month = 4;
  if (dzien == 0)
    day = 31;
  if (day == 26 && month == 4)
    day = 19;
  if (d == 28 && e == 6 && a > 10)
    dzien = 18;
    
cout << day << " " << month << endl;
}
