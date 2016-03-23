#include <iostream>
using namespace std;

int main() {
    int n, wynik = 1;
    cin >> n;
    while (wynik <= n) {
        cout << wynik << endl;
        wynik *= 2;
    }
}
