// Example program
#include <iostream>
#include <string>
#include <math.h>  

using namespace std;

int main()
{
{
int n, a=1;
cin>>n;
for(int i=2;i<=n;i++)
{
if(n%i==0)
{
a+=1;
}
}
if(a>2)
cout<<"zlozona";
else
cout<<"pierwsza";
}
	
	}