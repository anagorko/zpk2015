#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int k;
    cin >> k;
    int t[k+1];
    int z = 0;

    for (int i = 0; i <= k; i++)
        cin >> t[i];

    int i = 0;
    while(t[i] != 0 && i <= k) {
        i++;
    }
    if (t[i] == 0)
        z = (pow(2, i) - 1);
    else {
        for (int i = 0; i <= k; i++) {
            z += t[i] * pow(2, i);
        }
    }

    cout << z + 1 << endl;
}
