#include <iostream>
using namespace std;

int main() {
    long long i;
    cin >> i;

    // Program zatrzyma się tylko w przypadku, gdy i będzie postaci 2^n, gdzie n jest liczbą naturalną.

    while(i != 1 && i%2 == 0)
        i = i/2;

    if(i==1)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
