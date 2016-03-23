#include<iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int t[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> t[i][j];
    }

    int suma1, suma2 = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (t[i][k] < t[j][k])
                    suma2 += t[i][k];
                else
                    suma2 += t[j][k];
            }
            if (i == 0 & j == 1)
                suma1 = suma2;
            if (suma1 > suma2)
                suma1 = suma2;
            suma2 = 0;
        }
    }
    cout << suma1 << endl;
}
