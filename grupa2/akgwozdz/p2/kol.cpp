#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
 
int main() 
{
    double r, p, o;
    cin >> r;
    p=M_PI*r*r;
    o=2*r*M_PI;
    cout << setprecision(3) << fixed << p << endl;
    cout << setprecision(3) << fixed << o << endl;
}
