#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;
cin>> t;
int g,m,s;
g=t/3600;
m=(t-g*3600)/60;
s=(t-3600*g-60*m);
cout<<g<<"g"<<m<<"m"<<s<<"s"<<endl;
}
