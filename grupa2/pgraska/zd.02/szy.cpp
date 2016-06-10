#include <iostream>
#include <string>

using namespace std;

int main()
{
	int operacja;
	int k;
	string napis, nowy = "";
	cin >> operacja >> k >> napis;
	
	if (operacja == 1)
	{
		for (int i = 0;i < napis.length();i++)
		{
			char t = napis[i];
			if (t >= 'A' && t <= 'Z')
			{
				t = (t + k - 'A') % 26 + 'A';
			}
			else if (t >= 'a' && t <= 'z')
			{
				t = (t + k - 'a') % 26 + 'a';
			}
			
			nowy += t;
		}

		cout << nowy;
	}
	else if (operacja == 2)
	{
		for (int i = 0;i < napis.length();i++)
		{
			char t = napis[i];
			if (t >= 'A' && t <= 'Z')
			{
				t = (t - k);
				if (t < 'A')
					t += 26;
			}
			else if (t >= 'a' && t <= 'z')
			{
				t = (t - k);
				if (t < 'a')
					t += 26;
			}

			nowy += t;
		}

		cout << nowy;
	}

	system("pause");
	cin.get();
	return 0;
}
