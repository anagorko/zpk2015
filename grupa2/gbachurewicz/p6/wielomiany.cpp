#include <iostream>
#include <vector>
using namespace std;

class Polynomial
{
    vector<double> a;
    string name;
    double findRoot(double, double);

public:
    Polynomial();

    double getA(int) const;
    void setA(int, double);
    void setName(string);
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

ostream& operator<<(ostream &o, const Polynomial& p)
{
    o << p.name << ": " << p.getA(0) <<" ";

    for (int i = 1; i < p.deg()+ 1; i++)
        o << "+ " << p.getA(i) <<"x^" << i << " ";

    return o;
}


Polynomial::Polynomial() { //konstruktor tworzy pusty wektor z wyserowanymi wspó³czynnikami
}

double Polynomial::getA(int n) const{

    if (n >= a.size())
        cout<< "odmowa dostepu: wywolanie elementu wektora spoza zakresu dla: " << this ->name << endl;
    else return a[n];
}

void Polynomial::setName(string _name){
    name = _name;
}

void Polynomial::setA(int n, double b) {

    if (n < a.size())
        a[n] = b;

    else {
        a.resize(n + 1, 0.0);
        a[n] = b;
    }
}

int  Polynomial::deg() const {

	return a.size() - 1; //stopien wielominu to jego rozmiar - 1
}


Polynomial& Polynomial::operator+=(const Polynomial &q) {

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

const Polynomial Polynomial::operator+(const Polynomial &q) const {
    Polynomial c = *this;
    c += q; //korzystamy ze stworzonego juz operatora +=
    return c;
}

Polynomial& Polynomial::operator-=(const Polynomial &q) {

	for (int i = 0; i < q.deg() + 1; i++) {

		if (i < this->deg() + 1){
			this->setA(i, this->getA(i) - q.getA(i));
		}

		else {
			this->setA(i, -1*q.getA(i));
		}
	}
	return *this;
}

const Polynomial Polynomial::operator-(const Polynomial &q) const {
    Polynomial c = *this;
    c -= q;
    return c;
}

double Polynomial::v (double x) const {
    double suma = a[0];
    double suma1 = 1;
    for (int i = 1; i < a.size(); i++){
        if (a[i] != 0){
            suma1 = a[i];
            for (int j = 0; j < i; j++){
                suma1 *= x;
                }
            }
            suma += suma1;
    }
    return suma;
}

 bool Polynomial::operator==(const Polynomial &q) const {
    bool cos;

    if (this->deg() == q.deg()){
        for (int i = 0; i < this->deg() + 1; i++){
            if (this->a[i] == q.a[i])
                cos = true;
            else
                cos = false;
        }
    }
    else
        cos = false;

    return cos;
 }

bool Polynomial::operator!=(const Polynomial &q) const {

    return !(*this == q);
 }

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);

int main()
{
    Polynomial a, b, c;
    a.setName("a");
    b.setName("b");
    c.setName("c");
    a.setA(0, 1.3);
    a.setA(1, 3.5);
    a.setA(2, 2.1);
    b.setA(0, 0.7);
    b.setA(1, -0.5);

    cout << a << endl;
    cout << "stopien a to: " << a.deg() << endl;
    cout << b << endl;
    cout << "stopien b to: " << b.deg() << endl;

    cout << "Tak wyglada wynik dzialania a + b" << endl << a + b <<endl;

    a = a - b;
    cout <<"stopien a to: " <<a.deg()<<endl;
    cout<<"Tak wyglada a po operacji a = a - b" <<endl;
    cout << a << endl;

    a += b;
    cout <<"stopien a to: " <<a.deg()<<endl;
    cout<<"Tak wyglada a po operacji a += b" <<endl;
    cout << a << endl;

    cout << "wartosc wielomianu a w punkcie 3 rowna sie: " << a.v(3) <<endl;
    cout << "wartosc wielomianu b w punkcie -3 rowna sie: " << b.v(-3) <<endl;
    cout << "Czy wielomian a jest rowny b: ";
    if (a == b)
        cout << "TAK"<< endl;
    else
        cout << "NIE"<< endl;

    c.setA(0, 1.3);
    c.setA(1, 3.5);
    c.setA(2, 2.1);
    cout<<"Tak wyglada wielomian c" <<endl;
    cout << c << endl;

    cout << "Czy wielomian a jest rowny c: ";
    if (a == c)
        cout << "TAK"<< endl;
    else
        cout << "NIE"<< endl;

    cout << "Czy wielomian a jest rozny od b: ";
    if (a != b)
        cout << "TAK"<< endl;
    else
        cout << "NIE"<< endl;
    cout << "Czy wielomian a jest rozny od c: ";
    if (a != c)
        cout << "TAK"<< endl;
    else
        cout << "NIE"<< endl;
return 0;
}
