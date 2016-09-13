#include <iostream>
using namespace std;

int main()
{
  int x;
    cin >> x;
  int t[x];
  int result1;
  int result2;

  for(int i=0, i<x; i++)
    cin >> t[i];
  for(int i=0, i<x; i++)
  { 
    if (t[i]>result1)
          {result2=t[i];}
    else if (t[i]>result2)
          {result2=t[i];}
  }
  cout << result2 << endl;
}
