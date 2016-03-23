#include <iostream>
using namespace std;

int main() {
    int r, d, m;
    int a, b, c, k, l, p, q;
    cin >> r;
    if (r < 1899) {
        k = 23;
        l = 4;
    }
    else if (r < 2099) {
        k = 24;
        l = 5;
    }
    else {
        k = 24;
        l = 6;
    }
    a = r % 19;
    b = r % 4;
    c = r % 7;
    p = (19 * a + k) % 30;
    q = (2 * b + 4 * c + 6 * p + l) % 7;
    if (p == 29 && q == 6) {
        m = 4;
        d = 19;
    }
    else if (p == 28 && q == 6 && a > 10) {
        m = 4;
        d = 18;
    }
    else {
        if (22 + p + q <= 31) {
            m = 3;
            d = 22 + p + q;
        }
        else {
            m = 4;
            d = p + q - 9;
        }
    }
    cout << d << " " << m << endl;
}
