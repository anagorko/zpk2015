#include <iostream>
using namespace std;

long long rozwiazanie(long long p, long long q) {
	long long poczatek = 0;			// arbitralnie ustawiamy początek
	long long koniec = 1000000;		// i koniec przedziału
	long long x;
	
	while (poczatek < koniec) {
		x = (poczatek + koniec) / 2;	// wyznaczamy środek przedziału
		if (x * x * x + p * x == q)		// jeśli trafiliśmy,
			return x;					// to wyświetlamy liczbę, która spełnia równanie
		else if (x * x * x + p * x > q)		// jeśli wartość po lewej stronie jest większa niż po prawej,
			koniec = x;						// to szukamy w lewej części przedziału
		else
			poczatek = x + 1;				// w przeciwnym przypadku szukamy w prawej części przedziału
	}
	return -1;		// jeśli nie znaleźliśmy, zwracamy liczbę -1 (wybór arbitralny)
}

int main() {
	
	int z;
	cin >> z;
	
	long long p[z], q[z];
	for (int i = 0; i < z; i++)
		cin >> p[i] >> q[i];
	
	long long rozw;
	for (int i = 0; i < z; i++) {
		rozw = rozwiazanie(p[i], q[i]);
		if (rozw != -1)
			cout << rozw << endl;
		else
			cout << "NIE" << endl;
	}
}
