#include <iostream>
using namespace std;
int main()
{
    int n, a;
    cin >> n;
    if (n==0)
    a=1;
    else
    {
    if (n%4==1)
    a=2;
    if (n%4==2)
    a=4;
    if (n%4==3)
    a=8;
    if (n%4==0)
    a=6;
    }
    cout << a << endl;
}
