#include <iostream>
#include <vector>
using namespace std;

class Polynomial
{
	vector<double> a;
	double findRoot(double, double);

public:
	Polynomial() {
		a.push_back(0);
	}

	double getA(int i) const {
		if (a.size() < i + 1) {
			return 0;
		}
		else {
			return a[i];
		}
	}
	void setA(int i, double wartosc) {
		if (a.size() - 1 < i) {
			a.resize(i + 1, 0);
		}
		a[i] = wartosc;
	}

	int deg() const {

		int j = a.size() - 1;
		while (a[j] == 0) {
			j--;
			if (j == -1) {
				return -1;
			}
		}
		return j;

	}

	Polynomial& operator+=(const Polynomial &q) {

		for (int i = 0; i < q.a.size(); i++) {
			this->setA(i, q.a[i] + this->getA(i));
		}

		return *this;
	}
	const Polynomial operator+(const Polynomial &q) const {
		Polynomial p = Polynomial();
		p += *this;
		p += q;
		return p;
	}

	Polynomial& operator*=(const Polynomial &q) {
		Polynomial p = Polynomial();
		for (int i = 0; i < this->a.size(); i++) {
			for (int j = 0; j < q.a.size(); j++) {
				p.setA(i + j, this->a[i] * q.a[j] + p.getA(i + j));
			}
		}
		for (int i = 0; i < p.a.size(); i++) {
			this->setA(i, p.a[i]);
		}
		return *this;
	}
	const Polynomial operator*(const Polynomial &q) const {
		Polynomial p = Polynomial();

		p += *this;
		p *= q;
		return p;
	}

	Polynomial& operator-=(const Polynomial &q) {
		for (int i = 0; i < q.a.size(); i++) {
			this->setA(i, -q.a[i] + this->getA(i));
		}

		return *this;
	}// odejmowanie dwoch wielomianow
	const Polynomial operator-(const Polynomial &q) const {
		Polynomial p = Polynomial();
		p += *this;
		p -= q;
		return p;
	}

	bool operator==(const Polynomial &q) const {
		if (this->deg() == q.deg()) {
			for (int i = 0; i <= this->deg(); i++) {
				if (this->getA(i) != q.getA(i)) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}// czy wielomiany sa rowne?
	bool operator!=(const Polynomial &q) const {
		if (*this == q) {
			return false;
		}
		else {
			return true;
		}
	}// czy wielomiany sa rozne?

	double v(double x) const {
		double wynik = this->a[this->a.size() - 1];
		for (int i = this->a.size() - 1 - 1; i >= 0; i--) {
			wynik = this->a[i] + x*wynik;
		}
		return wynik;
	}// wartosc wielomianu dla argumentu x (za pomoca schematu Hornera)

	friend ostream& operator<<(ostream&, const Polynomial&);		// wypisywanie wielomianu


	const Polynomial differential() const {
		Polynomial p = Polynomial();

		for (int i = 1; i < this->a.size(); i++) {
			p.setA(i - 1, this->getA(i));
		}
		return p;
	}// pochodna wielomianu

	vector<double> rationalRoots() const;
	vector<double> realRoots() const;
};

ostream& operator<<(ostream& o, const Polynomial& p) {
	for (int i = 0; i < p.a.size(); i++) {
		o << p.a[i] << "x^" << i << "   ";
	}
	return o;
}

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R) {
	Polynomial Rpomoc;
	for (int i = 0; i <= W.deg(); i++) {
		Rpomoc.setA(i, W.getA(i));
	}
	Polynomial Qpomoc = Polynomial();
	while (Rpomoc.deg() >= P.deg()) {
		Polynomial pomoc = Polynomial();
		pomoc.setA(Rpomoc.deg() - P.deg(), -(Rpomoc.getA(Rpomoc.deg()) / P.getA(P.deg())));
		Qpomoc.setA(Rpomoc.deg() - P.deg(), Rpomoc.getA(Rpomoc.deg()) / P.getA(P.deg()));

		Polynomial mnozenie = P * pomoc;

		Rpomoc += mnozenie;
	}
	//kopiowanie wynikow dzielenia do wielomianow Q i R
	Q = Polynomial();
	for (int i = 0; i <= Qpomoc.deg(); i++) {
		Q.setA(i, Qpomoc.getA(i));
	}
	R = Polynomial();
	for (int i = 0; i <= Rpomoc.deg(); i++) {
		R.setA(i, Rpomoc.getA(i));
	}
}// dzielenie wielomianu - dzielimy wielomian W przez P,
 // otrzymujemy wielomian Q i reszte R


const Polynomial gcd(const Polynomial &A, const Polynomial &B) {
	Polynomial C = Polynomial();
	Polynomial Zerowy = Polynomial();
	Polynomial Q = Polynomial();
	Polynomial R = Polynomial();
	Polynomial APrim = Polynomial();
	for (int i = 0; i <= A.deg(); i++) {
		APrim.setA(i, A.getA(i));
	}
	Polynomial BPrim = Polynomial();
	for (int i = 0; i <= B.deg(); i++) {
		BPrim.setA(i, B.getA(i));
	}

	while (BPrim != Zerowy) {
		div(APrim, BPrim, Q, R);

		C = Polynomial();
		for (int i = 0; i <= R.deg(); i++) {
			C.setA(i, R.getA(i));
		}
		APrim = Polynomial();
		for (int i = 0; i <= BPrim.deg(); i++) {
			APrim.setA(i, BPrim.getA(i));
		}
		BPrim = Polynomial();
		for (int i = 0; i <= C.deg(); i++) {
			BPrim.setA(i, C.getA(i));
		}
	}
	return APrim;
}	// najwiekszy wspolny dzielnik wielomianow


int main() {

	Polynomial a, b;

	a.setA(0, 5);
	a.setA(1, -4);
	a.setA(2, 2);
	a.setA(3, -3);
	a.setA(4, 1);
	b.setA(1, 2);
	b.setA(2, 1);

	cout << "A: " << a << endl;
	cout << "B: " << b << endl;
	cout << endl;
	cout << "Stopien A: " << a.deg() << endl;
	cout << "Stopien B: " << b.deg() << endl;
	cout << endl;
	cout << " A + B: " << a + b << endl;
	cout << endl;
	cout << " A - B: " << a - b << endl;
	cout << endl;
	cout << " A * B: " << a * b << endl;
	cout << endl;
	cout << " A rowny B? : ";
	if (a == b)
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	cout << endl;
	cout << " A rozny od B? : ";
	if (a != b)
		cout << "TAK" << endl;
	else
		cout << "NIE" << endl;
	cout << endl;
	cout << "A': " << a.differential() << endl;
	cout << "B': " << b.differential() << endl;
	cout << endl;
	Polynomial Q = Polynomial();
	Polynomial R = Polynomial();
	div(a, b, Q, R);
    cout << endl;
	cout << "Q == " << Q << "\n";
	cout << "R == " << R << "\n";
	cout << "A w pkt x = 1: " << a.v(1) << endl;
	cout << "B w pkt x = 1: " << b.v(1) << endl;
	cout << endl;
	cout << "NWD dla A i B: " << gcd(a, b) << endl;

	system("pause");
}
