#include <iostream>
using namespace std;

int main()
{
	int n;
	int iloczyn_x = 1;
	do {
		cin >> n;
	} while (n < 0 || n > 12);

	if (n == 0)
		iloczyn_x = 1;
	else
	{
		for (int i = 1; i <= n; i++) {
			iloczyn_x *= i;
		}
	}
	cout << iloczyn_x << endl;

	system("pause");
	cin.get();
	return 0;
}
