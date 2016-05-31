#include <iostream>
#include <vector>

using namespace std;

class Zagadka {
public:
	unsigned long long p;
	unsigned long long q;

public:
	Zagadka(unsigned long long _p, unsigned long long _q) {
		p = _p;
		q = _q;
	}

	long long rozwiaz() {
		unsigned long long lewy = 0;
		unsigned long long prawy = 2000000;

		while (lewy < prawy) {
			unsigned long long x = (lewy + prawy) / 2;
			if (x*x*x+p*x == q) {
				return x;
			}
			else if (x*x*x+p*x > q) {
				prawy = x-1;
			}
			else {
				lewy = x+1;
			}
		}
		return -1;
	}

};



int main() {

	unsigned int z;
	cin >> z;
	
	unsigned long long p, q;

	vector<Zagadka*> zagadki;

	for (int i = 0; i < z; i++)
	{
		cin >> p;
		cin >> q;
		zagadki.push_back(new Zagadka(p,q));
	}

	for each(Zagadka* za in zagadki) {
		long long wynik = za->rozwiaz();
		if (wynik != -1) {
			cout << wynik << "\n";
		}
		else {
			cout << "NIE\n";
		}
	}

	for each(Zagadka* za in zagadki) {
		delete za;
	}

	zagadki.clear();																
	system("pause");
	return 0;
}
