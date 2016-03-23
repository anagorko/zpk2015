#include <iostream>
using namespace std;

int main() {
	
	int n;
	int licznik;
	cin >> n;
	
	int oceny[n];
	
	for (int i = 0; i < n; i++) {
		cin >> oceny[i];
	}
	
	for (int i = 1; i <= 6; i++) {
		licznik = 0;
		for (int j = 0; j <= n; j++) {
			if (oceny[j] == i) {
				licznik++;
			}
		}
		cout << licznik << " ";
	}
	
	
	
}
