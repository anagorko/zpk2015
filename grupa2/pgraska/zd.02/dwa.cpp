#include <iostream>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	int** tab = new int*[n];
	for (int i = 0;i < n;i++)
	{
		tab[i] = new int[m];
	}

	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < m;j++)
		{
			cin >> tab[i][j];
		}
	}

	int min = INT_MAX;

	for (int i = 0; i < n - 1; i++) 
	{
		for (int j = i + 1; j < n; j++) 
		{
			int wynik = 0;
			for (int k = 0; k < m; k++) 
			{
				if (tab[i][k] < tab[j][k])
				{
					wynik += tab[i][k];
				}
				else
				{
					wynik += tab[j][k];
				}
			}
			if (wynik < min)
			{
				min = wynik;
			}
		}
	}

	cout << min;

	system("pause");
	cin.get();
	return 0;
}
