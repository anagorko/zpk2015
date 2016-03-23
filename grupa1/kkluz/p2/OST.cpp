#include <iostream>
using namespace std;

	int main() 
{  
		int x, wynik;
		cin >> x;
		if (x == 0)
		{
			wynik = 1;
		}
		else 
		{
			if (x % 4 == 1) wynik = 2;
			if (x % 4 == 2) wynik = 4;
			if (x % 4 == 3) wynik = 8;
			if (x % 4 == 0) wynik = 6;
			
		}
	cout << wynik;
	
return 0;
}
