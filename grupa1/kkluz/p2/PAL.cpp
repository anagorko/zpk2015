#include <iostream>
#include <string>
using namespace std;

int main() 
{
	unsigned i;
	string slowo;
	int pal = 1;
	cin >> slowo;
	
	for (i = 0; i < slowo.length(); i++)
	{
		pal = pal*(slowo[i] == slowo[slowo.length() - 1 - i]);
	}
	if (pal) 
	{
		cout << "TAK";
	}
	else
	{
		cout << "NIE";
	}
return 0;
}
