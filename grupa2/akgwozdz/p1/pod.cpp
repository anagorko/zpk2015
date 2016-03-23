#include <iostream>
using namespace std;

int main()
{
    int a, b, k, l, x;
    cin >> a >> b >> k;
    l = 0;
    x = a;
    while (x <= b)
        {
        if (x % k == 0)
            {
            l++;
            x++;
            }
        else
            x++; 
        }
    cout << l << endl;
}
