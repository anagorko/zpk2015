#include <iostream>
using namespace std;
 
int main() 
{
    int n, i;
    cin >> n;
    int t[n];
    for (i = 0; i < n; i++)
        cin >> t[i];
    for (i = 0; i < n; i=i+2)
        cout << t[i] << " ";
    cout << endl;
    for (i = 1; i < n; i=i+2)
        cout << t[i] << " ";  
}
