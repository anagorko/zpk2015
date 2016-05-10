#include<iostream>
#include <vector>
#include <cmath>
using namespace std;


long long rozwiazanie (long long p, long long q)
{
	long long wynik = 0;
	long long poczatek = 1;
	long long koniec = 100000;
	long long x;

	while (poczatek < koniec -1 )
	{
		x = (poczatek + koniec +1 ) / 2;

		if ((x*(p + x*x)) >= q)
		{
			koniec = x;
			if ((x*(p + x*x)) == q)
			{
				wynik = x;
				break;
			}
		}
		else
			poczatek = x;
	}

	return wynik;
}

int main()
{
    long long z;
    cin >>z;

    long long p;
	long long q;

    vector <long long> wyniki;

    for (int i=0; i<z; i++)
    {
        cin >> p;
		cin >> q;
		wyniki.push_back(rozwiazanie(p,q));
    }

	for (int i = 0; i<z; ++i)
	{
		if (wyniki[i] == 0)
			cout << "NIE" << endl;
		else
		cout << wyniki[i] << endl;
	}
}

