#include <iostream>
using namespace std;

int main () {
    int a;
    int b;
    int c;
    cin >> a >> b >> c;;
    if (a+b>c && a+c>b && b+c>a) {cout << "TAK";}
    else {cout << "NIE";}
}
