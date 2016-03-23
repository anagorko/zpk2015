#include <iostream>
using namespace std;
int main()
{
int n,x,a=-1,b=-1;
cin>>n;
cin>>x;
int tab[n-1];
for(int i=0;i<=n-1;i++)
{
cin>>tab[i];
}
for(int i=0;i<=n-1;i++)
{
if(tab[i]==x)
{
a=i+1;
cout<<a;
i=n;
}
}
if(a==-1)
{
cout<<a;
}
cout<<" ";
for(int i=n-1;i>=0;i--)
{
if(tab[i]==x)
{
b=i+1;
cout<<b;
i=-1;
}
}
if(b==-1)
{
cout<<b;
}
}
