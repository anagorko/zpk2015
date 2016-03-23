#include <iostream>
#include <string>
using namespace std;
int main()
{
int n,j=0,d=0,t=0,c=0,p=0,s=0;
cin>>n;
int oceny[n-1];
for(int i=0;i<=n-1;i++)
{
cin>>oceny[i];
}
for(int i=0;i<=n-1;i++)
{
if(oceny[i]==6)
s=s+1;
else if(oceny[i]==5)
p=p+1;
else if(oceny[i]==4)
c=c+1;
else if(oceny[i]==3)
t=t+1;
else if(oceny[i]==2)
d=d+1;
else
j=j+1;
}
cout<<j<<" "<<d<<" "<<t<<" "<<c<<" "<<p<<" "<<s;
}
