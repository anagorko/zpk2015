#include <iostream>
using namespace std;

int wicemistrz(int t[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int m = 0, max = t[0];
        for (int j = 1; j <= i; j++)
            if (t[j] > max) {
                m = j;
                max = t[m];
            }
        t[m] = t[i];
        t[i] = max;
    }
    return t[n - 2];
}

int main() {
    int n;
    cin >> n;
    int t[n];

    for(int i = 0; i < n; i++)
        cin >> t[i];

    cout << wicemistrz(t, n) << endl;
}
