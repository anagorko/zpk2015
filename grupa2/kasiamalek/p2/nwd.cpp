#include <iostream>
using namespace std;
int main()
{
int n,a,b,c;
cin>>n;
int t[n-1];
for(int i=0;i<=n-1;i++)
{
cin>>t[i];
}
a=t[0];
for(int i=0;i<=n-2;i++)
{
b=t[i+1];
while(b!=0)
{
c=a%b;
a=b;
b=c;
}
}
cout<<a;
}
