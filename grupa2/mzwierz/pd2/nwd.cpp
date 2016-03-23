#include<iostream>
using namespace std;

int nwd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;

    while (a != b) {
        if (a > b) a = a - b%a;
        else b = b - a%b;
    }
    return a;
}

int main() {
    int a;
    cin >> a;
    int b;
    cin >> b;
    cout << nwd(a,b) << endl;
}
