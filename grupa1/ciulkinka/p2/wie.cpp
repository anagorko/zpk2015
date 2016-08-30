#include <iostream>
using namespace std;


int main()
{
    int i, d, m;
    int a, b, c, e, f, g, h, k, l, p;
    cin >> i;
    //1
    a = i % 19;
    //2
    b = i / 100;
    //3
    c = i % 100;
    //4
    d = b / 4;
    //5
    e = b % 4;
    //6
    f = (b + 8) / 25;
    //7
    g = (b - f + 1) / 3;
    //8
    h = ((19 * a) + b - d - g + 15) % 30;
    //9
    i = c / 4;
    //10
    k = c % 4;
    //11
    l = (32 + (2 * e) + (2 * i) - h - k) % 7;
    //12
    m = (a + (11 * h) + 22 * l) / 451;
    //13
    p = (h + l - (7 * m) + 114) % 31;
    //14
    d = p + 1;
    //15
    m = (h + l - (7 * m) + 114) / 31;

    cout << d << " " << m;

    return 0;
}
