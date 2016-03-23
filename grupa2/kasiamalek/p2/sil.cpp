#include <iostream>
using namespace std;
int main()
{
int silnia=1
;
int n;
cin>>n;
if(n==0)
cout<<1;
else{
for(int i=1;i<=n;i++)
silnia=silnia*i;
cout<<silnia;
}
}
