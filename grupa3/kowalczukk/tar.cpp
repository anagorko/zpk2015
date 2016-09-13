#include <iostream>
using namespace std;

long long tartaglia(long long p, long long q) 
{
	long long poczatek = 0;			
	long long koniec = 1000000;		
	long long x;

	while (poczatek < koniec) 
	{
		x = (poczatek + koniec) / 2;	
		if (x * x * x + p * x == q)		
			return x;					
		else if (x * x * x + p * x > q)		
			koniec = x;						
		else
			poczatek = x + 1;				
	}
	return -1;		
}

int main()
{

	int z;
	cin >> z;

	long long p[z], q[z];
	for (int i = 0; i < z; i++)
		cin >> p[i] >> q[i];

	long long a;
	for (int i = 0; i < z; i++) 
	{
		a = tartaglia(p[i], q[i]);
		if (a != -1)
			cout << a << endl;
		else
			cout << "NIE" << endl;
	}
}
