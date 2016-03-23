#include <iostream>
using namespace std;

int main () {
    int i;
    cin >> i;

    while (i != 1) {
    if (i % 2 == 0) {i = i / 2;}
    else {i = 3 * i + 3;}
    if (i % 3 == 0) {break;}
    }
    if (i==1) {cout << "TAK";}
    else {cout << "NIE";}
}
