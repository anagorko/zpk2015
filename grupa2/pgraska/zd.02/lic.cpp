#include <iostream>
using namespace std;

int main()
{
	int n;
	int licznik = 0;
	
		cin >> n;
		cin.get();
		for (int i = 2; i <= n-1; i++)
		{
			if (n % i == 0)
			{
				licznik++;
			}
		}
		if (licznik == 0 && n > 1)
		{
			cout << "pierwsza" << endl;
		}
		else
		{
			cout << "zlozona" << endl;
		}

	system("pause");
	cin.get();
	return 0;
}


