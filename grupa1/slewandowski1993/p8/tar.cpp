#include<iostream>
#include <vector>
#include <cmath>
using namespace std;


long long rozw(long long p, long long q)
{
	long long wyn = 0;
	long long pocz = 1;
	long long kon = 100000;
	long long x;

	while (pocz < kon-1)
	{
		x = (pocz + kon+1)/2;

		if ((x*(p+x*x))>=q)
		{
			kon = x;
			if ((x*(p+x*x))==q)
			{
				wyn = x;
				break;
			}
		}
		else
			pocz = x;
	}
	return wyn;
}

int main()
{
    long long z;
    cin >>z;

    long long p;
	long long q;

    vector <long long> wyn;

    for (int i=0; i<z; i++)
    {
        cin >> p;
		cin >> q;
		wyn.push_back(rozw(p,q));
    }

	for (int i = 0; i<z; ++i)
	{
		if (wyn[i] == 0)
			cout << "NIE" << endl;
		else
		cout << wyn[i] << endl;
	}
}
