#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

using namespace std;

int main()
{
	double r;
	cin >> r;
	double pole = M_PI * r * r;
	pole = round(pole * 1000.0) / 1000.0;

	double obwod = 2.0 * M_PI * r;
	obwod = round(obwod * 1000.0) / 1000.0;

	cout << pole << endl;
	cout << obwod << endl;

	system("pause");
	cin.get();
	return 0;
}
