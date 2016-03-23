#include <iostream>
using namespace std;

int sortowanie(int t[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int m = 0, maks = t[0];
        for (int j = 1; j <= i; j++)
            if (t[j] > maks) {
                m = j;
                maks = t[m];
            }
        t[m] = t[i];
        t[i] = maks;
    }
    return t[n - 2];
}

int main() {
    int n;
    cin >> n;
    int t[n];

    for(int i = 0; i < n; i++)
        cin >> t[i];

    cout << sortowanie(t, n) << endl;
}
