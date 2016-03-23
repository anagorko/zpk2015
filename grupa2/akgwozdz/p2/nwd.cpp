#include <iostream>
using namespace std;

int main()
{
    int n, m, i, j, nwd;
    cin >> n;
    int t[n];
    for (i = 0; i<n; i++)
        cin >> t[i]; 
    m = t[0];
    for (i = 1; i<n; i++)
        {
            if (t[i] < m)
            m = t[i];
        }
    nwd = 1;
    bool dzielnik=true;
    for(j=1; j<=m; j++)
    {
        for(int i=0; i<n; i++)
        {
        if (t[i] % j != 0)
            dzielnik = false;
        }
        if (dzielnik==true)
            nwd = j;
        else
            dzielnik=true;
    }
    cout << nwd << endl;
}
