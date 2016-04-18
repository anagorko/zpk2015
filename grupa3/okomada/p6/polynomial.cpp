#include<iostream>
#include <vector>
using namespace std;

class Polynomial
{
	vector<double> a;

	double findRoot(double, double);

public:
	Polynomial();

	double getA(int) const;
	void setA(int, double);

	int deg() const;

	Polynomial& operator+=(const Polynomial &q);
	const Polynomial operator+(const Polynomial &q) const;

	Polynomial& operator*=(const Polynomial &q);
	const Polynomial operator*(const Polynomial &q) const;

	Polynomial& operator-=(const Polynomial &q);
	const Polynomial operator-(const Polynomial &q) const;

	bool operator==(const Polynomial &q) const;
	bool operator!=(const Polynomial &q) const;

	double v(double x) const;

	friend ostream& operator<<(ostream&, const Polynomial&);

	const Polynomial differential() const;

	vector<double> rationalRoots() const;
	vector<double> realRoots() const;
};
// konstruktor 
Polynomial::Polynomial() {

};

double Polynomial::getA(int i) const {
	return a[i];
};

void Polynomial::setA(int n, double val){
	for (int i = a.size(); i < n + 1; i++){
		a.push_back(0);
	}
	a[n] = val;
}

int  Polynomial::deg() const {
	int d = a.size() - 1;
	return d;
}

Polynomial& Polynomial::operator += (const Polynomial &q) {
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < this->deg() + 1){
			this->setA(i, this->getA(i) + q.getA(i));
		}
		else {
			this->setA(i, q.getA(i));
		}
	}
	return *this;
}

Polynomial& Polynomial::operator -= (const Polynomial &q) {
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < this->deg() + 1){
			this->setA(i, this->getA(i) - q.getA(i));
		}
		else {
			this->setA(i, -1 * q.getA(i));
		}
	}
	return *this;
}

const Polynomial Polynomial::operator +(const Polynomial &q) const {
	Polynomial* result = new Polynomial();
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < this->deg() + 1){
			result->setA(i, this->getA(i) + q.getA(i));
		}
		else {
			result->setA(i, q.getA(i));
		}
	}
	return *result;
}

const Polynomial Polynomial::operator-(const Polynomial &q) const {
	Polynomial* result = new Polynomial();
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < this->deg() + 1){
			result->setA(i, this->getA(i) - q.getA(i));
		}
		else {
			result->setA(i, -1 * q.getA(i));
		}
	}
	return *result;
}

Polynomial& Polynomial::operator *= (const Polynomial &q) {
	int c_i = 0;
	Polynomial result = Polynomial();
	Polynomial* mult1 = this;
	Polynomial mult2 = q;
	// wyrównywanie wektorów
	for (int i = 0; i < mult1->deg() + q.deg() + 1; i++){
		result.setA(i,0);
	}
	for (int i = q.deg() + 1; i < result.deg() + 1; i++){
		mult2.setA(i, 0);
	}
	for (int i = this->deg() + 1; i < result.deg() + 1; i++){
		mult1->setA(i, 0);
	}

	for (int i = 0; i < result.deg() + 1; i++) {
		c_i = 0;
		for (int j = 0; j < i + 1; j++){
			c_i += mult1->getA(i)*mult2.getA(i);
		}
		result.setA(i, c_i);
	}
	for (int i = 0; i < result.deg() + 1; i++){
		this->setA(i, result.getA(i));
	}
	return *this;
} 

bool Polynomial::operator==(const Polynomial &q) const {
	bool equal = 1;
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < a.size()){
			equal = equal * (a[i] == q.getA(i));
		}
		else {
			equal = equal * (0 == q.getA(i));;
		}
	}
	return equal;
};

bool Polynomial::operator!=(const Polynomial &q) const {
	bool equal = 1;
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < a.size()){
			equal = equal * (a[i] == q.getA(i));
		}
		else {
			equal = equal * (0 == q.getA(i));;
		}
	}
	return !equal;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);

int main()
{
	Polynomial p = Polynomial();
	Polynomial q = Polynomial();
	Polynomial r = Polynomial();
	p.setA(1, 1);
	q.setA(1, 3);
	cout << p.getA(1)<< endl;
	p += q;
	cout << p.getA(1) << endl;
	q -= q;
	cout << q.getA(1) << endl;
	bool t= q != p;
	cout << t << endl;
	getchar();
	return 0;
}
