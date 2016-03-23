#include <iostream>
using namespace std;

int NWD(int m, int n)
{
    while (m != 0 && n != 0)
    {
        if (m % n == 0 || n % m == 0)
        {
            if (m >= n)
                return n;
            else
                return m;
        }
        if (m > n)
            m = m % n;
        else
            n = n % m;
    }
}

int main() 
{
    int x;
    cin >> x;
    int t[x];
    
    for (int i = 0; i < x; i++)
        cin >> t[i];
    int y;
    y = NWD(t[0], t[1]);
    
    for (int j = 2; j <= x-1; j++)
        y = NWD(y, t[j]);
    cout << y;
}
