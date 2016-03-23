#include <iostream>
using namespace std;
int main()
{
int n,a=0,b=0;
cin>>n;
int p[n-1];
for(int i=0;i<=n-1;i++)
{
cin>>p[i];
}
for(int i=0;i<=n-1;i++)
{
if(p[i]>a)
{
a=p[i];
}
}
for(int i=0;i<=n-1;i++)
{
if(p[i]>b&&p[i]<a)
{
b=p[i];
}
}
cout<<b;
}
