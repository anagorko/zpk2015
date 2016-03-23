#include <iostream>
using namespace std;
 
int main() 
{
    int n, m, l, i, j, a, b;
    a=100001;
    b=0;
    cin >> n >> m;
    int t[n][m];
    for (j = 0; j<n; j++)
        for (i = 0; i<m; i++)
            cin >> t[j][i];

    for (j = 0; j<n-1; j++)
    for (l = 1; j+l<n; l++)
        {
        for (i = 0; i<m; i++)
        {
            if (t[j][i]<t[j+l][i])
                b=b+t[j][i];
            else
                b=b+t[j+l][i];
        }
            if (b<a)
                {a=b;
                b=0;}
            else
                b=0;
        }
        cout << a;
}
