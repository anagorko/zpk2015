#include <iostream>
using namespace std;
 
int main() 
{
    int n, x, i, a, b;
    a = -1;
    b = -1;
    cin >> n >> x;
    int t[n];
    for (i = 0; i < n; i++)
        cin >> t[i];
    for (i = 0; i <= n; i++)
        {
        if (t[i]==x)
            {
            b = i+1;
            }
        if (t[n-i]==x)
            {
            a = n-i+1;
            }
        }
cout << a << " " << b << endl;
}
