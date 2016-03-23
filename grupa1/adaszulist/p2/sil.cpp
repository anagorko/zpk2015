#include <iostream>
using namespace std;

int main() {
    int n;
    int silnia = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        silnia *= i;
    }
    cout << silnia << endl;
    return 0;
}
