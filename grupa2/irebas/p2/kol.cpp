#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
	
	float r;
	cin >> r;
	float ob = 2*M_PI*r;
	float pole = M_PI*r*r;
	cout << setprecision(3) << fixed;
	cout << ob << endl;
	cout << pole << endl;
	
}
