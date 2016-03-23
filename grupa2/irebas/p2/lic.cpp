#include <iostream>
using namespace std;

int main() {
	int n;
	int wynik;
	int licznik;
	licznik = 0;
	cin >> n;
	
	for (int i = 1; i<=n; i++) {
		wynik = n % i;
		if (wynik == 0) {
			licznik++;
		}
	}
	
	if (licznik == 2) {
		cout << "Pierwsza";
	}
	else {
		cout << "Złożona";
	}

	
}
