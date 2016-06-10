#include <iostream>

using namespace std;

int main()
{
	int rok;
	cin >> rok;

	int A, B;
	if (rok >= 1800 && rok < 1900)
	{
		A = 23;
		B = 4;
	}
	else if (rok >= 1900 && rok < 2100)
	{
		A = 24;
		B = 5;
	}
	else if (rok >= 2100)
	{
		A = 24;
		B = 6;
	}
	else
	{
		cout << "Rok nie miesci sie w zakresie 1800-2200!";
		return 1;
	}

	int a = rok % 19;
	int b = rok % 4;
	int c = rok % 7;
	int d = (a * 19 + A) % 30;
	int e = (2 * b + 4 * c + 6 * d + B) % 7;
	int w = d + e;

	if (w <= 9)
	{
		cout << 22 + w << " 3";
	}
	else
	{
		cout << w - 9 << " 4";
	}

	system("pause");
	cin.get();
	return 0;
}
