#include <iostream>
using namespace std;
int main()
{
    int n, ostat;
    cin >> n;
    if (n==0)
    ostat=1;
    else
    {
    if (n%4==1)
    ostat=2;
    if (n%4==2)
    ostat=4;
    if (n%4==3)
    ostat=8;
    if (n%4==0)
    ostat=6;
    }
    cout << ostat;
}
