
#include <iostream>

using namespace std;

int main()
{
    int x,A,B,d,m,a,b,c,e;

    cin >>x;

    if (x == 1981 || x == 2076 || x == 2133 || x == 2201 || x == 2296)
    {
		d = 19;
		m = 4;
		cout << d << " " << m << endl;
		return 0;
	}
	else if (x == 1954 || x == 2049 || x == 2106)
	{
		d = 18;
		m = 4;
		cout << d << " " << m << endl;
		return 0;
	}
	else if (x >= 1800 && x <= 1899)
	{
		A = 23;
		B = 4;
	}
	else if (x >= 1900 && x <= 2099)
	{
		A = 24;
		B = 5;
	}
	else if (x >= 2100 && x <= 2199)
	{
		A = 24;
		B = 6;
	}
	else if (x == 2200)
	{
		A = 25;
		B = 0;
	}

    a = x % 19;
	b = x % 4;
	c = x % 7;
	d = ((a * 19) + A) % 30;
	e = (2 * b + 4 * c + 6 * d + B) % 7;

	if (d + e < 10)
    {
		m = 3;
		d = d + e + 22;
		cout << d << " " << m << endl;
	}
	else
    {
		m = 4;
		d = d + e - 9;
		cout << d << " " << m << endl;
	}

    return 0;
}

