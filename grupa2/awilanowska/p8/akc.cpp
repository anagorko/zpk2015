#include <iostream>
using namespace std;

int pierwsze_wystapienie(int element, int tab[], int n) {				// znajdujemy pierwsze wystapienie danego elementu w tablicy,
	int poczatek = 0;													// wykorzystując wyszukiwanie binarne
	int koniec = n - 1;
	int srodek;
	
	while (poczatek < koniec) {
		srodek = (poczatek + koniec) / 2;
		if (tab[srodek] >= element)
			koniec = srodek;
		else
			poczatek = srodek + 1;
	}
	
	return poczatek;
}

int ostatnie_wystapienie(int element, int tab[], int m, int n) {		// znajdujemy ostatnie wystąpienie danego elementu w tablicy,
	int poczatek = m;													// wykorzystując wyszukiwanie binarne
	int koniec = n - 1;
	int srodek;
	
	while (poczatek < koniec) {
		srodek = (poczatek + koniec + 1) / 2;
		if (tab[srodek] <= element)
			poczatek = srodek;
		else
			koniec = srodek - 1;
	}
	
	return koniec;
}

int main() {
	
	int n;
	cin >> n;
	
	int tab[n];
	for(int i = 0; i < n; i++)
		cin >> tab[i];
	
	int q;
	cin >> q;
	
	int tab2[q];
	for (int i = 0; i < q; i++)
		cin >> tab2[i];
	
	int poczatek;
	for (int i = 0; i < q; i++) {
		if (tab[pierwsze_wystapienie(tab2[i], tab, n)] != tab2[i])		// gdy nie ma takiego elementu w tablicy
			cout << 0 << endl;											// - wyświetlamy stosowny komunikat
		else if (tab[pierwsze_wystapienie(tab2[i], tab, n)] != tab[pierwsze_wystapienie(tab2[i], tab, n) + 1])	// gdy jest jedynie jeden element w tablicy
			cout << 1 << endl;																					// - wyświetlamy stosowny komunikat
		else {
			poczatek = pierwsze_wystapienie(tab2[i], tab, n);
			cout << (ostatnie_wystapienie(tab2[i], tab, poczatek, n) - poczatek + 1) << endl;	// obliczamy ilość wystąpień
		}			
	}	
}
