#include <iostream>
using namespace std;

int main(){
    int a;
    int b;
    int k;
    cin >> a >> b >> k;

    int licznik = 0;
    while ( a <= b) {
        if ( a%k == 0) {
            licznik = licznik +1;
            }
        a = a + 1;
        }
    cout << licznik;

}
