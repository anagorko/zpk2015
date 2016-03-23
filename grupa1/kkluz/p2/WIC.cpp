#include <iostream>
using namespace std;
 
int main() 
{
    int n, i, a, b;
    cin >> n;
    int t[n];
    
    for (i = 0; i<n; i++)
        cin >> t[i];
    a=b=0; 
    for (i = 0; i<n; i++)
        {
            if (t[i]>a)
            {
                b=a;
                a=t[i];
            }
            else if (t[i]>b)
            {
                b=t[i];
            }
        }
    cout << b;
    
return 0;
}
