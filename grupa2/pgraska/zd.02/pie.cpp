#include <iostream>
using namespace std;

int main()
{
	
	int n,x;
	int licznik = 0;
	cin >> n;
	cin	>> x;
	int* tab_cen = new int[n];
	for (int i = 0; i < n; i++)
		cin >> tab_cen[i];
		
	for (int i = 0; i < n; i++)
	{
		if (x == tab_cen[i]) {
			cout << i + 1 << " ";
			licznik++;
			break;
		}
	}
	if (licznik == 0)
		cout << -1 << " ";
	licznik = 0; 
	
	for (int i = n; i >= 0; i--)
	{
		if (x == tab_cen[i]) {
			cout << i + 1 << " ";
			licznik++;
			break;
		}
	}
	if (licznik == 0)
		cout << -1 << " ";


	system("pause");
	cin.get();
	return 0;
}
