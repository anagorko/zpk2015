#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n];

    for (int i = 0; i < n; i++)
        cin >> t[i];

    int o[6];
    for (int j = 0; j < 6; j++)
        o[j] = 0;

    for (int j = 0; j < 6; j++)
        for (int i = 0; i < n; i++)
            if (t[i] == j + 1)
                o[j]++;

    for (int j = 0; j < 6; j++)
        cout << o[j] << " ";

    cout << endl;
}
