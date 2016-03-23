#include <iostream>
using namespace std;

int main()
{
    int c, d, l;
    char a, b, z;
    cin >> a >> b;
    d=a-48;
    if (b=='A')
        c=10;
    else if (b=='B')
        c=11;
    else if (b=='C')
        c=12;
    else if (b=='D')
        c=13;
    else if (b=='E')
        c=14;
    else if (b=='F')
        c=15;
    else
        c=b-48;
    l = d * 16 + c;
    z = l;
    cout << l << endl;
    cout << z << endl;
}
