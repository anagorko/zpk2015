#include <iostream>
using namespace std;

int main()
{
    int a, b, k, x, y, i;
    cin >> a >> b >> k;
    x = 0;
    y = 0;
    if (a<k or b<k)
        {
        i = 0;
        }
    else
        {
        x = a/k;
            {
            if (b>=2*k)
                {
                x = 2*x;
                y = b/k - 2;
                    if (a>=2*k)
                    y = 2*y;
                }
            }
        i = x+y;
        }
    cout << i << endl;   
}
