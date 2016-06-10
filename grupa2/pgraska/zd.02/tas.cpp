#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int* liczby = new int[n];
	for (int i = 0;i < n;i++)
	{
		cin >> liczby[i];
	}

	int najwieksza = 0;

	for (int i = 0;i < n - 1;i++)
	{
		for (int j = i + 1;j < n;j++)
		{
			if (liczby[i] != liczby[j] && j - i > najwieksza)
			{
				najwieksza = j - i;
			}
		}
	}

	if (najwieksza != 0)
	{
		cout << najwieksza;
	}
	else
	{
		cout << "BRAK";
	}

	system("pause");
	cin.get();
	return 0;
}
