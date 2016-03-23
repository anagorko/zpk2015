#include <iostream>
using namespace std;

int main()
{
	int n, i;
	cin >> n;
	if (n==0)
		cout << 1;
	else
	{
		int silnia=1;
		for (i=1; i<=n; i++)
		{
		silnia=silnia*i;
		}	
		cout << silnia;
	}
	
	
return 0;	
}
