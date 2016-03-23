#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n];
    int maksimum1 = 0;
    int maksimum2 = 0;

    for (int i = 0; i < n; ++i)
        cin >> t[i];

    int i = 0;
    while (t[i] == t[n - 1] && i < (n - 1)) {
        ++i;
    }
    if (t[i] != t[n - 1]) {
        maksimum1 = n - 1 - i;
    }

    i = n - 1;
    while (t[i] == t[0] && i > 0) {
        --i;
    }
    if (t[i] != t[0]) {
        maksimum2 = i;
    }

    if (maksimum1 == 0 && maksimum2 ==0)
        cout << "BRAK" << endl;
    else
        cout << max(maksimum1, maksimum2) << endl;
}
