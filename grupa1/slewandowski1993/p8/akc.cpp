#include <iostream>
#include <vector>
using namespace std;

int szukaj (vector <int> t, int lic)
{
int wyst1;
int wyst2;
int pocz = 0;
int kon = t.size() - 1;
int sr;
int p2 = pocz;
int k2 = kon;
bool log = true;

    while (pocz < kon)
	{
		sr = (pocz + kon ) / 2;
		if (t[sr] >= lic)
		{
			if ((t[sr] == lic) && log)
			{
				log = false;
				p2 = sr;
				k2 = kon;
			}
			else
                kon = sr;
		}
		else
			pocz = sr + 1;
	}
	wyst1 = pocz;

	pocz = p2;
	kon = k2;

	while (pocz < kon)
	{
		sr = (pocz + kon + 1) / 2;
		if (t[sr] <= lic)
			pocz = sr;
		else
			kon = sr - 1;
	}
	wyst2 = kon;

	if (t[wyst1] == lic)
		return (wyst2 - wyst1 + 1);
	else
		return 0;
}


int main()
{
	int n;
	int q;
	vector <int> tab_pom;
	vector <int> wyn;
	cin >> n;

	for (int i = 0; i<n; ++i)
	{
		int pom;
		cin >> pom;
		tab_pom.push_back(pom);
	}

	cin >> q;

	for (int i = 0; i<q; ++i)
	{
		int szuk;
		cin >> szuk;
		wyn.push_back(szukaj(tab_pom, szuk));
	}

	for (int i = 0; i<q; ++i)
	{
		cout << wyn[i] << endl;
	}
}
