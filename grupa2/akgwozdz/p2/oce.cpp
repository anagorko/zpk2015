#include <iostream>
using namespace std;
 
int main() 
{
    int n, i, a, x;
    x=0;
    cin >> n;
    int t[n];
    for (i = 0; i<n; i++)
        cin >> t[i];
        
    for (a = 1; a<=6; a++)       
        {
        for (i = 0; i<n; i++)
        {
            if (t[i]==a)
            x++;
        }
        cout << x << " ";
        x=0;
        }
}
