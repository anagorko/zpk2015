#include<iostream>
using namespace std;

// funkcja NWD - kurs
int NWD(int a, int b) {
    int r = a % b;
	while (r != 0) {
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

int main() {
    int n;
    cin >> n;
    int t[n];
    for (int i = 0; i < n; i++)
        cin >> t[i];

    int wynik;
    wynik = NWD(t[0], t[1]);
    for (int i = 2; i <= n-1; i++)
        wynik = NWD(wynik, t[i]);
    cout << wynik << endl;
}
