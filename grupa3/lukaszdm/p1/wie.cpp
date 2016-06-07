#include <iostream>
using namespace std;

int main() {
    int a, b, k, ilosc;
    cin >> a >> b >> k;
    if (a % k == 0 || b % k == 0)
        ilosc = 1 + (b-a)/k;
    else
        if (a + k - a % k <= b){
            a += k - a % k;
            ilosc = 1 + (b-a)/k;
        }
        else
            ilosc = 0;
    cout << ilosc << endl;
}
