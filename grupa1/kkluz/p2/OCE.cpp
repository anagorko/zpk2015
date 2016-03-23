#include <iostream>
#include <string>
using namespace std;

int main() 
{
	int n, i, j;
	int o[6];
	cin >> n;

	for (i = 0; i < 6; i++)
	{
		o[i] = 0;
	}
	
	for (i = 0; i < n; i++)
	{
		cin >> j;
		o[j-1] ++;
	}
	for (i = 0; i < 6; i++)
	{
		cout << o[i] << ' ';
	}
	
return 0;
}
