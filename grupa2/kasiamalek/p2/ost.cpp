#include <iostream>
using namespace std;
int main()
{
//sposob nie spelnia warunku limitu czasu
int n,a=1;
cin>>n;
if(n==0)
a=1;
else
for(int i=1;i<=n;i++)
{
a=a*2;
if(a>10)
a=a%10;
}
if(a<10)
cout<<a;
else
{
cout<<a%10;
}
}
