#include <iostream>
using namespace std;

int main() {
    int n, x, a = -2, b = -2;
    cin >> n >> x;
    int t[n];

    for (int i = 0; i < n; i++)
        cin >> t[i];

    int i = 0;
    while(t[i] != x && i < n) {
        i++;
    }
    if (t[i] == x)
        a = i;

    for (int i = 0; i < n; i++)
        if (t[i] == x)
            b = i;

    cout << a + 1 << " " << b + 1 << endl;
}
