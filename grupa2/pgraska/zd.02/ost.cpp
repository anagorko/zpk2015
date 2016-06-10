#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;

	int podstawa = 2;
	int potega = 1;

	while (n > 0)
	{
		if (n & 1)
			potega = (potega * podstawa) % 10;
		podstawa = (podstawa * podstawa) % 10;
		n /= 2;
	}

	cout << potega;

	system("pause");
	cin.get();
	return 0;
}
