#include <iostream>
using namespace std;

int mistrz(int t[], int n) {
    int m = 0;
    for (int i = 0; i < n; i++)
        if (t[i] > m)
            m = t[i];
    return m;
}
int wice(int t[], int n) {
    int w = 0;
    for (int i = 0; i < n; i++){
        if (t[i] > w && t[i] != mistrz(t,n))
            w = t[i];}
    return w;
}

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i=0; i<=n-1; i++)
        cin >> t[i];
    cout << wice(t,n) << endl;
}
