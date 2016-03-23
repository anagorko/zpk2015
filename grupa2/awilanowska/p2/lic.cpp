#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    bool warunek = true;
    for (int i = 2; i * i <= n; i++) {
        warunek = warunek && (n % i != 0);
    }
    if (warunek)
        cout << "pierwsza" << endl;
    else
        cout << "zlozona" << endl;
}
