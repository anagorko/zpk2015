#include <iostream>
#include <vector>
using namespace std;

int szukaj (vector <int> t, int liczba)
{
int wystapienie1;
int wystapienie2;
int poczatek = 0;
int koniec = t.size() - 1;
int srodek;
int p2 = poczatek;
int k2 = koniec;
bool log = true;

    while (poczatek < koniec)
	{
		srodek = (poczatek + koniec ) / 2;
		if (t[srodek] >= liczba)
		{
			if ((t[srodek] == liczba) && log)
			{
				log = false;
				p2 = srodek;
				k2 = koniec;
			}
			else
                koniec = srodek;
		}
		else
			poczatek = srodek + 1;
	}
	wystapienie1 = poczatek;

	poczatek = p2;
	koniec = k2;

	while (poczatek < koniec)
	{
		srodek = (poczatek + koniec + 1) / 2;
		if (t[srodek] <= liczba)
			poczatek = srodek;
		else
			koniec = srodek - 1;
	}
	wystapienie2 = koniec;

	if (t[wystapienie1] == liczba)
		return (wystapienie2 - wystapienie1 + 1);
	else
		return 0;
}


int main()
{
	int n;
	int q;
	vector <int> tablica_pomiarow;
	vector <int> wyniki;
	cin >> n;   //liczba pomiarow

	for (int i = 0; i<n; ++i)
	{
		int pomiar;
		cin >> pomiar;      //pomiary
		tablica_pomiarow.push_back(pomiar);
	}

	cin >> q;   //liczba zapytan

	for (int i = 0; i<q; ++i)
	{
		int szukany;
		cin >> szukany;
		wyniki.push_back(szukaj(tablica_pomiarow, szukany));
	}

	for (int i = 0; i<q; ++i)
	{
		cout << wyniki[i] << endl;
	}
}
