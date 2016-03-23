#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int t[n][m];
    int minimum = 100000;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> t[i][j];

    for (int i = 0; i < (n - 1); i++) {
        for (int k = i + 1; k < n; k++) {
            int wynik = 0;
            for (int j = 0; j < m; j++) {
                if (t[i][j] < t[k][j])
                    wynik += t[i][j];
                else
                    wynik += t[k][j];
            }
            if (wynik < minimum)
                minimum = wynik;
        }
    }

    cout << minimum << endl;
}
