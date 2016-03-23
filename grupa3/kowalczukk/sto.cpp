#include <iostream>
using namespace std;

int main() {
    int a, b, k;
    cin >> a >> b >> k;
    int n=0;
    if (a > b) {
        if (b >= 2*k) {
            n=2* (b/k + a/k - 2);
        }
        else if ( b>=k && b < 2*k) {
            n= a/k;
        }
    }
    else {
        if (a >= 2*k) {
            n= 2* (b/k + a/k - 2);
        }
        else if ( a>=k && a < 2*k) {
            n= b/k;
        }
     }

    cout << n << endl;
}
