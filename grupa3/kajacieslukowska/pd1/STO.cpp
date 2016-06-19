#include <iostream>
using namespace std;

int main(){
    int a, b, k;
    cin >> a >> b >> k;

    int d;
    if( a > b) {
        d = b;
        b = a;
        a = d;
    }

    int licznik;
    if( b < k)
        licznik = 0;
    if( a >= k && a < 2*k )
        licznik = b/k;
    if( a >= 2*k )
        licznik = 2*(a/k) + 2*((b-2*k)/k);

    cout << licznik << endl;
}


