#include <iostream>
using namespace std;

int main()
{
    int x, l, a;
    l = 0;
    cin >> x;
    while (x != -1)
    {
        a = x;
        cin >> x;
        if (a < x)
            l++;
    }
    cout << l << endl;
}
