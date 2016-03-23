#include <iostream>
#include <math.h>
using namespace std;
 
int main() 
{
    unsigned int n, i;
    bool pierwsza;
    cin >> n;
    pierwsza = true;
    if(n<2)
        pierwsza = false;
    for (i = 2; i<=sqrt(n); i++)
        if(n%i==0)
            pierwsza = false;

    if (pierwsza == true)
        cout << "pierwsza" << endl;
    else
        cout << "zlozona" << endl;  
}
