#include <iostream>
using namespace std;
int main()
{
int n;
cin>>n;
int tab[n-1];
for(int i=0;i<=n-1;i++)
{
cin>>tab[i];
}
for(int i=0;i<=n-1;i=i+2)
{
cout<<tab[i];
cout<<" ";
}
cout<<endl;
for(int i=1;i<=n-1;i=i+2)
{
cout<<tab[i];
cout<<" ";
}
}
