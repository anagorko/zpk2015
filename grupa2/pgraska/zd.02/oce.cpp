#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int* oceny = new int[n];
	int ilosci[6] = { 0, 0, 0, 0, 0, 0 };

	for (int i = 0;i < n;i++)
	{
		cin >> oceny[i];
	}

	for (int i = 0;i < n;i++)
	{
		ilosci[oceny[i] - 1]++;
	}

	for (int i = 0;i < 6;i++)
	{
		cout << ilosci[i] << " ";
	}

	system("pause");
	cin.get();
	return 0;
}
