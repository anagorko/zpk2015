#include <iostream>
using namespace std;

int NWD(int a, int b) {
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

long long NWW(int a, int b) {
    return (long long) a * b / NWD(a, b);
}

int main() {
    int z;
    cin >> z;
    int t[z][2];

    for(int i = 0; i < z; ++i)
        cin >> t[i][0] >> t[i][1];

    for(int i = 0; i < z; ++i)
        cout << (long long) NWW(t[i][0], t[i][1]) / t[i][1] << endl;
}
