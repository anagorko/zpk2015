#include <iostream>
using namespace std;

int main() 
{
    int n;
    bool p = true;
    cin >> n;
    
    for (int i = 2; i * i <= n; i++)
        p = p && n % i != 0;
    if (p)
        cout << "pierwsza" << endl;
    else
        cout << "zlozona" << endl;
        
return 0;
}
