#include <iostream>
using namespace std;

int main() {
    int r, a, b, c, d, e, dzi, mie, A, B ;
    cin >> r ;
    if (r<1800 | r>=2200) return 0;
    if (r<1900) {A=23; B=4;}
    else { A=24; if (r<2100) {B=5;} else {B=6;} }
    dzi=22;
    mie=3;
    a = r % 19;
    b = r % 4;
    c = r % 7;
    d = (a *19 + A) % 30;
    e = (2*b + 4*c + 6*d + B) % 7;
    dzi = d + e + 22;
    if (dzi>31) { cout<< dzi-31<< " " << mie+1; }
    else {cout<< dzi <<" " << mie;}
}
