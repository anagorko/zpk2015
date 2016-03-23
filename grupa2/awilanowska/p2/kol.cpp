#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int main() {
    double r;
    cin >> r;
    cout << setprecision(3) << fixed;
    cout << M_PI * r * r << endl;
    cout << 2 * M_PI * r << endl;
}
