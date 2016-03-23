#include <iostream>
using namespace std;

int main()
{
    int x, y, n;
    cin >> n;
    x = 1;
    y = 1;
    while (x <= n)
    {
        y=y*x;
        x++;
    }
    cout << y << endl;   
}
