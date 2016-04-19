#include<cmath>
#include<iostream>
#include<vector>
using namespace std;

class Polynomial
{
	vector <double> a;

	double findRoot(double, double);

public:
	Polynomial() {}

	double getA(int) const;
	void setA(int, double);

	int deg() const;

	Polynomial & operator+=(const Polynomial & q);
	const Polynomial operator+(const Polynomial & q) const;

	Polynomial & operator*=(const Polynomial & q);
	const Polynomial operator*(const Polynomial & q) const;

	Polynomial & operator-=(const Polynomial & q);
	const Polynomial operator-(const Polynomial & q) const;

	bool operator==(const Polynomial & q) const;
	bool operator!=(const Polynomial & q) const;

	double v(double x) const;

	friend ostream & operator<<(ostream &, const Polynomial &);

	const Polynomial differential() const;

	vector <double> rationalRoots() const;
	vector <double> realRoots() const;
};

double Polynomial::getA(int i) const {
	return a.at(i);
}

void Polynomial::setA(int i, double v) {
	if (a.size() < i + 1)
		a.resize(i + 1, 0);
	a.at(i) = v;
}

int Polynomial::deg() const {
	if (1 == a.size() && 0 == a.at(0))
		return -1;
	else
		return a.size() - 1;
}

Polynomial & Polynomial::operator+=(const Polynomial & q) {
	if (deg() < q.deg())
		a.resize(q.deg() + 1, 0);

	for (int i = 0; i < q.deg() + 1; ++i)
		a.at(i) += q.getA(i);

	// czyszczenie zer z konca, ale do momentu,
	// gdy jest chociaz jeden element (nawet zero)
	// zeby wielomian sie wyswietlil
	while (0 == a.at(a.size() - 1) && a.size() > 1)
		a.pop_back();

	return *this;
}

const Polynomial Polynomial::operator+(const Polynomial & q) const {
	return Polynomial(*this) += q;
}

Polynomial & Polynomial::operator*=(const Polynomial & q) {
	vector <double> pomocniczy(a.size() + q.deg() + 1, 0);

	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < q.deg() + 1; ++j) {
			pomocniczy.at(i + j) += a.at(i) * q.getA(j);
		}
	}

	a = pomocniczy;
	return *this;
}

const Polynomial Polynomial::operator*(const Polynomial &q) const {
	return Polynomial(*this) *= q;
}

Polynomial & Polynomial::operator-=(const Polynomial & q) {
	if (deg() < q.deg())
		a.resize(q.deg() + 1, 0);

	for (int i = 0; i < q.deg() + 1; ++i)
		a.at(i) -= q.getA(i);

	// czyszczenie zer z konca, ale do momentu,
	// gdy jest chociaz jeden element (nawet zero)
	// zeby wielomian sie wyswietlil
	while (0 == a.at(a.size() - 1) && a.size() > 1)
		a.pop_back();

	return *this;
}

const Polynomial Polynomial::operator-(const Polynomial & q) const {
	return Polynomial(*this) -= q;
}

bool Polynomial::operator==(const Polynomial & q) const {
	if (deg() != q.deg())
		return false;
	else {
		for (int i = 0; i < a.size(); ++i) {
			if (a.at(i) != q.getA(i))
				return false;
		}
	}
	return true;
}

bool Polynomial::operator!=(const Polynomial & q) const {
	return !(*this == q);
}

double Polynomial::v(double x) const {
	double wartosc = { a.at(0) };

	for (int i = 1; i < a.size(); ++i)
		wartosc += a.at(i) * pow(x, i);

	return wartosc;
}

ostream & operator<<(ostream & os, const Polynomial & q) {
	bool pierwszyWyraz = true;

	if (-1 == q.deg())
		// do wyswietlania wielomianow W(x) = 0,
		// w szczegolnosci Q(x), gdy st. W(x) < st. P(x) (dzielenie wielomianow)
		cout << q.getA(0);
	else {
		for (int i = q.deg(); i >= 0; --i) {
			if (0 != q.getA(i)) {
				// znak "+" (ale nie jest wyswietlany na poczatku)
				if (q.getA(i) > 0 && pierwszyWyraz == false)
					cout << "+";

				// wyraz
				if (0 == i)
					cout << q.getA(i);
				else if (1 == i) {
					if (1 == q.getA(i))
						cout << "x";
					else if (-1 == q.getA(i))
						cout << "-x";
					else
						cout << q.getA(i) << "x";
				}
				else {
					if (1 == q.getA(i))
						cout << "x^" << i;
					else if (-1 == q.getA(i))
						cout << "-x^" << i;
					else
						cout << q.getA(i) << "x^" << i;
				}
				pierwszyWyraz = false;
			}
		}
	}
	return os;
}

const Polynomial Polynomial::differential() const {
	Polynomial pochodna;

	pochodna.a.resize(deg(), 0);
	pochodna.a.insert(pochodna.a.begin(), a.begin() + 1, a.end());
	
	for (int i = 0; i < pochodna.a.size(); ++i)
		pochodna.a.at(i) *= (i + 1);

	return pochodna;
}

void div(const Polynomial & W, const Polynomial & P, Polynomial & Q, Polynomial & R) {
	if (W.deg() >= P.deg()) {
		// zmienne pomocnicze
		bool pierwszyKrok = { true };
		double pierwszyWyraz;
		vector <double> pomocniczy(W.deg() + 1, 0);
		vector <double> reszta(W.deg() + 1, 0);

		// wektor, ktory zawiera dzielnik przesuniety o roznice stopni dzielnej i dzielnika
		for (int i = 0; i < P.deg() + 1; ++i)
			pomocniczy.at(i + W.deg() - P.deg()) = P.getA(i);

		do {
			if (pierwszyKrok) {
				// 1. pierwszy wyraz W(x) jest dzielony przez pierwszy wyraz P(x)
				Q.setA(W.deg() - P.deg(), W.getA(W.deg()) / P.getA(P.deg()));
				pierwszyWyraz = Q.getA(W.deg() - P.deg());
				
				// 2. Powstaje reszta R(x) = W(x) - pierwszyWyraz * P(x)
				for (int i = 0; i < reszta.size(); ++i)
					reszta.at(i) = W.getA(i) - pierwszyWyraz * pomocniczy.at(i);

				// porzadkowanie wektora reszt
				while (0 == reszta.at(reszta.size() - 1) && reszta.size() > 1)
					reszta.pop_back();
			}
			else {
				// 3. pierwszy wyraz R(x) (reszty) jest dzielony przez pierwszy wyraz P(x)
				Q.setA(reszta.size() - 1 - P.deg(), reszta.at(reszta.size() - 1) / P.getA(P.deg()));
				pierwszyWyraz = Q.getA(reszta.size() - 1 - P.deg());

				// uaktualnienie wektora pomocniczego
				pomocniczy.clear();
				pomocniczy.resize(reszta.size(), 0);
				for (int i = 0; i < P.deg() + 1; ++i)
					pomocniczy.at(i + reszta.size() - 1 - P.deg()) = P.getA(i);

				// 4. Powstaje nowa reszta R(x) = R(x) - pierwszyWyraz * P(x)
				for (int i = 0; i < reszta.size(); ++i)
					reszta.at(i) = reszta.at(i) - pierwszyWyraz * pomocniczy.at(i);

				// porzadkowanie wektora reszt
				while (0 == reszta.at(reszta.size() - 1) && reszta.size() > 1)
					reszta.pop_back();
			}

			pierwszyKrok = false;
		} while (reszta.size() - 1 >= P.deg());

		// przepisanie wektora reszt
		for (int i = reszta.size() - 1; i >= 0; --i)
			R.setA(i, reszta.at(i));
	}
	else {
		Q.setA(0, 0);
		R = W;
	}
}

const Polynomial gcd(const Polynomial & W, const Polynomial & P) {
	Polynomial w = { W }, p = { P }, gcd;
	double reszta = 0;
	int stopienReszty = { 0 };

	if (-1 == P.deg()) {
		if (-1 == W.deg()) {
			gcd.setA(0, 0);
			return gcd;
		}
		else
			return W;
	}
	else {
		do {
			Polynomial q, r;

			div(w, p, q, r);
			w = p;
			p = r;
			reszta = r.getA(0);
			stopienReszty = r.deg();

			if (-1 == stopienReszty)
				gcd = w;
			else if (0 != reszta && 0 == stopienReszty) {
				// gdy przypadek z niezerowa reszta,
				// np. gcd(2x^2 + 6x + 3, 2x + 1)
				gcd.setA(0, 1);
				break;
			}

		} while (0 != reszta && -1 != stopienReszty);
	}
	return gcd;
}
