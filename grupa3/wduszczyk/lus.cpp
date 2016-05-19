#include <iostream>
using namespace std;
int main()
{
int n,a;
a=0;
cin>>n;
while(n/10!=0)
{
a*=10;
a+=(n%10);
n/=10;
}
a*=10;
cout<<a+(n%10)<<endl;
}