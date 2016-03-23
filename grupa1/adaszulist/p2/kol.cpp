#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
double pr;
double pole, obw;

cin >> pr;

pole = M_PI * pr * pr;
obw = 2 * M_PI * pr;

cout.precision(3);
cout << fixed << pole << endl << obw;

return 0;
}
