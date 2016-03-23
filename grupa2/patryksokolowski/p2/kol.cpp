#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double pole(double r) {
    double pole;
    pole = M_PI*r*r;
    return pole;
}

double obwod(double r) {
    double obwod;
    obwod = 2*M_PI*r;
    return obwod;
}

int main()
{
    double r;
    cin >> r;
    cout << setprecision(3) << fixed << pole(r) << endl << obwod(r);
}
