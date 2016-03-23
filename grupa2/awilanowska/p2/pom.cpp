#include <iostream>
using namespace std;

int main() {
    int liczba_pomiarow = 0, m, n;
    cin >> n;
    while (n != -1) {
        while (n == 0)
            cin >> n;
        m = n;
        cin >> n;
        if (m != n)
            liczba_pomiarow++;
    }
    cout << liczba_pomiarow << endl;
}
