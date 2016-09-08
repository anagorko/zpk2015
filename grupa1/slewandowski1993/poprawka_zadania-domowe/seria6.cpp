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

/* konstruktor */
Polynomial::Polynomial() {

};

/* zwraca wspolczynnik dla danego stopnia n */
double Polynomial::getA(int i) const {
    if (i < a.size()){
        return a[i];
    }
    else{
        return 0;
    }
};

/* ustawia wspolczynnik dla danego stopnia n */
void Polynomial::setA(int n, double val){
	for (int i = a.size(); i < n + 1; i++){
		a.push_back(0);
	}
	a[n] = val;
}

/* zwraca najwyzsze n przy ktorym stoi niezerowy wspolczynnik */
int  Polynomial::deg() const {
	int d = a.size() - 1;
	return d;
}

/* dodawanie wielomianow */
Polynomial& Polynomial::operator += (const Polynomial &q) {
    int st_max = max(deg(), q.deg());
    for (int i = 0; i <= st_max ; ++i){
        setA(i, getA(i) + q.getA(i));
        }
    return *this;
}

const Polynomial Polynomial::operator +(const Polynomial &q) const {
    Polynomial result;
    int st_max=max(deg(), q.deg());

    for(int i=0; i<=st_max; i++)
        {
        result.setA(i,getA(i)+q.getA(i));
        }
    return result;
}

/* odejmowanie wielomianow */
Polynomial& Polynomial::operator -= (const Polynomial &q) {
    int st_max = max(deg(), q.deg());
        for (int i = 0; i <= st_max ; ++i){
            setA(i, getA(i) - q.getA(i));
        }
    return *this;
}



const Polynomial Polynomial::operator-(const Polynomial &q) const {
    Polynomial result;
    int st_max=max(deg(), q.deg());

    for(int i=0; i<=st_max; i++)
        {
        result.setA(i, getA(i) - q.getA(i));
        }
    return result;
}

/* mnozenie wielomianow */
Polynomial& Polynomial::operator *= (const Polynomial &q) {
    Polynomial result;
    int stopien=(deg()+q.deg());
    result.setA(stopien,0);

    for(int i=0; i<=deg(); i++){
        for(int j=0; j<=q.deg(); j++) {
            result.setA(i+j,result.getA(i+j)+getA(i)*q.getA(j)) ;
        }
        int j=0;

        }
    return result;
}

/*
const Polynomial operator*(const Polynomial &q) const{
    Polynomial result;
    int stopien=(deg()+q.deg());
    result.setA(stopien,0);

    for(int i=0; i<=deg(); i++){
        for(int j=0; j<=q.deg(); j++) {
            result.setA(i+j,u.getA(i+j)+getA(i)*q.getA(j)) ;
        }
        j=0;

        }
    return result;
}
*/

/* sprawdza czy wielomiany sa rowne */
bool Polynomial::operator==(const Polynomial &q) const {
	if (deg()!=q.deg()) {
    return false;
    }

	bool equal = 1;
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < a.size()){
			equal = equal * (a[i] == q.getA(i));
		}
		else {
			equal = equal * (0 == q.getA(i));
		}
	}
	return equal;
};

/* sprawdza czy wielomiany nie sa rowne */
bool Polynomial::operator!=(const Polynomial &q) const {
    if (deg()==q.deg()) {
    return false;
    }

	bool equal = 1;
	for (int i = 0; i < q.deg() + 1; i++) {
		if (i < a.size()){
			equal = equal * (a[i] == q.getA(i));
		}
		else {
			equal = equal * (0 == q.getA(i));;
		}
	}
	return equal==0;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);

int main()
{
	Polynomial p = Polynomial();
	Polynomial q = Polynomial();
	Polynomial r = Polynomial();
	p.setA(1, 5);
	q.setA(1, 2);
	r.setA(2, 3);
	cout << p.getA(1)<< endl;
	cout << q.getA(1)<< endl;
	cout << r.getA(1)<< endl;
	cout << r.getA(2)<< endl;
	p += q;
	cout << p.getA(1) << endl;
	q -= p;
	cout << q.getA(1) << endl;
	q -= q;
	cout << q.getA(1) << endl;
	q.setA(1, 2);
	r += q;
    cout << r.getA(1)<< endl;
	cout << r.getA(2)<< endl;
	bool t= q != p;
	cout << t << endl;
	return 0;
}
