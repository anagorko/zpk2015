#include <iostream>
#include <string>

using namespace std;

int main()
{
    int a, b, k;
    cin >> a >> b >> k;
    
    if (a < k && b < k)
        cout << 0;
    else {
        if (a == b && a == k)
            cout << 1;
        else {
            
            if (a < 2*k && b < 2*k) {
                if (a >= b)
                    cout << (a/k)*2;
                else
                    cout << (b/k)*2;
            }
            else {
     
                if (a == b && a == 2 * k)
                    cout << 4;
                
                else {
                    if (a >= b)
                        cout << (a/k)*2 + ((b - 2*k)/k)*2;
                    else
                        cout << (b/k)*2 + ((a - 2*k)/k)*2;
                        
                }
            }    
        }
    }
return 0;
}
