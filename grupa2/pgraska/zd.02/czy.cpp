#include <iostream>

using namespace std;

int main()
{
	unsigned long long int i;
	cin >> i;

	while (i != 1) 
	{
		if (i == 2) 
		{
			cout << "TAK";
			return 0;
		}
		else if (i == 3) 
		{
			cout << "NIE";
			return 0;
		}
		else 
		{
			if (i % 2 == 0)
			{
				i /= 2;
			}
			else
			{
				i = 3 * i + 3;
			}
		}
	}

	system("pause");
	cin.get();
	return 0;
}
