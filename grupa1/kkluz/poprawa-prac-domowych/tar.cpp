#include<iostream>
#include <vector>
#include <cmath>
using namespace std;


long long odpowiedz(long long p, long long q)
{
	long long szukany_x;
	long long y;
	long long s;
	long long e;



	szukany_x = -1;
	s = 1;
	e = 1000000;

	y = s;
	if (y*p + pow(y,3)-q == 0)
	{
		return y;
	}

	y = e;
	if (y*p + pow(y,3)-q == 0)
	{
		return y;
	}
	while (s < e -1 )
	{
		y = (s + e +1 ) / 2;
		if (y*p + pow(y,3)-q >= 0)
        {

			e = y;
			if (y*p + pow(y,3)-q == 0)
			{
				szukany_x = y;
				break;
			}
		}
		else
			s = y;
	}

	return szukany_x;
}

int main()
{
	int liczba_zagadek;
	long long p;
	long long q;
	vector <long long> wyniki;

	cin >> liczba_zagadek;
	for (int i = 0; i < liczba_zagadek; i++)
	{
		cin >> p;
		cin >> q;
		wyniki.push_back(odpowiedz(p,q));
	}

	for (int i = 0; i<liczba_zagadek; ++i)
	{
		if (wyniki[i] == -1)
			cout << "NIE" << endl;
		else
		cout << wyniki[i] << endl;
	}
}
