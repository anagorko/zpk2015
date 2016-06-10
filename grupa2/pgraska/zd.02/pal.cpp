#include <iostream>
#include <string>

using namespace std;

int main()
{
	string slowo;
	cin >> slowo;
	bool palindrom = true;

	for (int i = 0, j = slowo.length() - 1;i < slowo.length() / 2;i++, j--)
	{
		if (slowo[i] != slowo[j])
		{
			palindrom = false;
			break;
		}
	}

	if(palindrom)
	{
		cout << "TAK";
	}
	else
	{
		cout << "NIE";
	}

	
	system("pause");
	cin.get();
	return 0;
}
