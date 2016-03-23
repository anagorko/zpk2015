#include <iostream>
using namespace std;

int main() {
	int n;
	int cena;
	cin >> n;
	cin >> cena;
	int a[n];
	int suma;
	bool czy_jest;
	czy_jest = false;
	suma = 0;
	for (int i=0; i < n; i++) {
		cin >> a[i];
	}
	/* cout << endl << cena << endl; */
	
	for (int i = 0; i < n; i++) {
		if (a[i] == cena) {
		cout << i + 1;
		czy_jest = true;
		break;
		}
	}
	
	for (int i = n; i >= 0; i--) {
		if (a[i] == cena) {
		cout << i + 1 << endl;
		break;
		}
	}
	
	if (czy_jest == false) {
		cout << "-1 -1";
	}
	
}
