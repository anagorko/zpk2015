#include <iostream>
using namespace std;

int main() {
    int a, b, k;
    cin >> a >> b >> k;
    if (a < k || b < k)
        cout << 0 << endl;
    else {
        if (a >= 2 * k && b >= 2 * k)
            cout << 2 * ((a / k) + (b / k)) - 4;
        else if (a >= k || b >= k) {
            if (a >= k && a < 2 * k)
                cout << (b / k) << endl;
            else
                cout << (a / k) << endl;
        }
    }
}
