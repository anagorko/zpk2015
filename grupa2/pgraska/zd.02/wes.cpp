#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	int z;
	cin >> z;
	for (int i = 0;i < z;i++)
	{
		int n, d;
		cin >> n >> d;
		int pocz = 0;
		int malpki = 0;
		bool* klatki = new bool[n];
		for (int j = 0;j < n;j++)
		{
			klatki[j] = false;
		}

		bool skacze = true;
		while (skacze)
		{
			pocz += d;

			if (pocz >= n)
				pocz -= n;

			if (klatki[pocz] == true)
			{
				skacze = false;
			}
			else
			{
				klatki[pocz] = true;
				malpki++;
			}
		}
		cout << malpki << endl;
	}

	system("pause");
	cin.get();
	return 0;
}
