#include <iostream>
using namespace std;
 
int main()
{
  int n;
  int silnia = 1;
 
  cin>>n;
 

  for(int i=n;i>1;i--)
    silnia*=i;
 
 
  cout<< silnia << endl;
}
 