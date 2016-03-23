#include <iostream>
using namespace std;
 
int main() 
{
    int n, i, a, b;
    cin >> n;
    int p[n];
    for (i = 0; i<n; i++)
        cin >> p[i];
    a=b=0; 
    for (i = 0; i<n; i++)
        {
            if (p[i]>a)
            {
                b=a;
                a=p[i];
            }
            else if (p[i]>b)
            {
                b=p[i];
            }
        }
    cout << b;
}
