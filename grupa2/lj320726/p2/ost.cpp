#include <iostream>
#include <cmath>

using namespace std;

int main()
{
int a;
cin >> a;
int b;
if(a==0)
{
    cout << "1";
    return 0;
}

b=a%4;

switch (b)
{
    case 1: 
        cout<<2;
        break;
    case 2:
        cout << 4;
        break;
    case 3:
        cout << 8;
        break;
    case 0:
        cout<<6;
        break;
}
}
