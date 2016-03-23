#include <iostream>
using namespace std;

int main()
{
    int n, a;
    int l = 0;
    cin >> n;
    while (n != -1)
    {
        a = n;
        cin >> n;
        if (a < n)
            l++;
    }
    cout << l << endl;
    
return 0;
}
