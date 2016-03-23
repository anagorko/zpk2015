#include <iostream>
using namespace std;

int main() {
    int n,x,p,o ;
    p=0;
    o=0;

    cin >> n  ;
    if (n<2) {return 0;}

    int c[n], a[n/2], b[n/2];

    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (i%2 == 0 ) {a[i/2] = c[i];p++;}
            else { b[i/2] = c[i];o++;}
       }
    for (int i = 0; i < p; i++) {
        cout << a[i] << " " ; }

    cout<< endl;

    for (int i = 0; i < o; i++) {
        cout << b[i] <<" "; }
}
