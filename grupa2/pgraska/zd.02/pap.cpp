#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	int k;
	cin >> k;
	int* papryczki = new int[k + 1];
	int wynik = 0;

	for (int i = 0;i < k + 1;i++)
	{
		cin >> papryczki[i];
	}

	for (int i = 0; i <= k; i++) 
	{
		wynik += papryczki[i] * pow(2, i);
	}

	wynik++;

	cout << wynik;

	system("pause");
	cin.get();
	return 0;
}
