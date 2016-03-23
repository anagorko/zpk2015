#include <iostream>
#include <string>
using namespace std;
int main()
{
int n,a,b,l=0;
string slowo;
cin>>slowo;
n=slowo.size();
a=n/2;
for(int i=0;i<=a-1;i++)
{if(slowo[i]==slowo[n-1-i])
l=l+1;
}
if(l==a)
cout<<"TAK";
else
cout<<"NIE";
}
