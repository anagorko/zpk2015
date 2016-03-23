#include<iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];

    int maxx = t[0];
    for (int i = 1; i < n; i++) {
        if (maxx < t[i])
            maxx = t[i];
    }

    int wic = 0;
    for (int i = 0; i < n; i++) {
        if (t[i]> wic && t[i] < maxx)
            wic = t[i];
    }
    cout << wic << endl;
}
