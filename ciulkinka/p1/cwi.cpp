#include <iostream>
using namespace std;

int main() {
    long long int x, y;
    cin >> x >> y;
    if (x == 0 && y == 0)
        cout << 0 << endl;
    else if (x == 0)
        cout << "OY" << endl;
    else if (y == 0)
        cout << "OX" << endl;
    else if (x > 0) {
        if (y > 0)
            cout << "I" << endl;
        else if (y < 0)
            cout << "II" << endl;
    } else if (x < 0) {
        if (y < 0)
            cout << "III" << endl;
        else if (y > 0)
            cout << "IV" << endl;
    }

    return 0;
}
