#include <iostream>
using namespace std;

int main()
{
    int x, y, a, b, c, d, e;
    cin >> x >> y;
    a = (x % 10) * 2;
    b = a + 5;
    c = b * 50;
    d = c + 1764;
    e = d - y;
    cout << e << endl;
}
