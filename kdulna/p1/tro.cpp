#include <iostream>
using namespace std;

int main() {
    unsigned int a, b, c;
    cin >> a >> b >> c;
    if (a + b > c && b + c > a && a + c > b)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
