#include <iostream>
using namespace std;
bool the_lower(string x, string y) 
  {
    if (x.length() < y.length())
      return true;
      if (x.length() > y.length())
        return false;
          if (x.length() == y.length())
          {
            for (int i = 0; i < x.length(); i++){
              if (x[i] < y[i])
                return true;
                  if (x[i] > y[i])
                    return false;
    }
  return false;
  }
}
int main() {
string x, y, sign;
cin >> x >> sign >> y;
  bool lower = the_lower(x, y);
  bool bigger = the_lower(y, x);
  bool equal = (lower == false && bigger == false);
  bool not_equal = (equal == false);
  bool bigger_equal = (bigger == true || equal == true);
  bool lower_equal = (lower == true || equal == true);
    if (sign == "<")
    {
      if (lower)
        cout << "YES" << endl;
      else
        cout << "NO" << endl;
    }
    if (sign == ">"){
      if (bigger)
          cout << "YES" << endl;
      else
          cout << "NO" << endl;
    }
      if (sign == "==")
      {
          if (equal)
            cout << "YES" << endl;
          else
            cout << "NO" << endl;
      }
          if (sign == "!="){
          if (not_equal)
              cout << "YES" << endl;
          else
              cout << "NO" << endl;
      }
          if (sign == ">="){
          if (bigger_equal)
              cout << "YES" << endl;
          else
              cout << "NO" << endl;
        }
            if (sign == "<="){
            if (lower_Equal)
          cout << "YES" << endl;
            else
          cout << "NO" << endl;
        }
}
