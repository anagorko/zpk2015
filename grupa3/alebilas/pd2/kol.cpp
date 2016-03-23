#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){

double r;
double pole;
double obwod;

cin >> r;

pole = M_PI * pow(r,2);
obwod = 2 * M_PI * r;

cout << setprecision(3) << fixed << pole << endl;
cout << setprecision(3) << fixed << obwod << endl;

}
