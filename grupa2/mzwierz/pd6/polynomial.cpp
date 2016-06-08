#include<iostream>
#include<vector>
using namespace std;


class Polynomial
{
    vector<double> a;

    double findRoot(double x1, double x2)
     {
        if (v(x1) == 0.0)
            return x1;
        if (v(x2) == 0.0)
            return x2;
        else
            cout <<"pierwiastek nie zostal znaleziony"<<endl;

    };

public:
    Polynomial();

    double getA(int) const;
    void setA(int, double);

    int deg() const;

    Polynomial& operator+=(const Polynomial &q);            //dodawanie wielomianów
    const Polynomial operator+(const Polynomial &q) const;

    Polynomial& operator-=(const Polynomial &q);            //odejmowanie wielomianów
    const Polynomial operator-(const Polynomial &q) const;

    bool operator==(const Polynomial &q) const;             //czy wielomiany równe
    bool operator!=(const Polynomial &q) const;             //czy wielomiany rózne

    double v(double x) const;           //wartosc wielomianu dla danego argumentu x

   friend ostream& operator<<(ostream&, const Polynomial&);

    const Polynomial differential() const;      //pochodna wielomianu

};

// ROZWI¥ZANIE

Polynomial::Polynomial() {
	a.push_back(0);
}

    double Polynomial::getA(int i) const
    {
        return this->a[i];
    }
    void Polynomial::setA(int i, double n)
    {
        if (this->a.size()<i+1)
            this->a.resize(i+1);
        this->a[i]=n;
    }
    double Polynomial::v(double x) const {

        double b = a[a.size() - 1];

        for (int i = a.size() - 2; i >= 0; i--) {
		b = a[i] + b * x;
	}

	return b;

}

    int Polynomial::deg() const
    {
        if (a.size() - 1)
            return (a.size()-1);
        else if(a[0])
                return 0;
            else
                return -1;
    }

    Polynomial& Polynomial::operator+=(const Polynomial &q) {

        if (q.deg() > this->deg())
            this->a.resize(q.deg() + 1,0);

        for (int i = 0; i <= q.deg(); i++)
            this->a[i] += q.getA(i);

        return *this;

    }

    const Polynomial Polynomial::operator+(const Polynomial &q) const {
        return Polynomial(*this) += q;
    }

     Polynomial& Polynomial::operator-=(const Polynomial &q)
      {

        if (q.deg() > this->deg())
            this->a.resize(q.deg(),0);

        for (int i = 0; i <= q.deg(); i++)
            this->a[i] -= q.getA(i);

        return *this;

    }

    const Polynomial Polynomial::operator-(const Polynomial &q) const {
        return Polynomial(*this) -= q;
    }

    bool Polynomial::operator==(const Polynomial &q) const
    {
       bool rowne = true;

        if (a.size() - 1 != q.deg())
            return false;
        else
            for (int i = a.size() - 1; i >= 0; i--)
                if (a[i] != q.getA(i))
                    rowne = false;

        return rowne;

    }

    bool Polynomial::operator!=(const Polynomial &q) const
    {
         bool rozne = false;

        if (a.size() - 1 != q.deg())
            return true;
        else
            for (int i = a.size() - 1; i >= 0; i--)
                if (a[i] != q.getA(i))
                    rozne = false;

        return rozne;
    }

    const Polynomial Polynomial::differential() const
     {
        Polynomial p;
        if (a.size() > 1) {
            for (int i = 1; i < a.size(); i++) {
                if (a[i])
                    p.setA(i - 1, a[i] * i);
            }
            return p;
        }
        else
            p.setA(0, 0);
    }


    ostream& operator<<(ostream &os, const Polynomial &p)
    {

	if (p.deg() == -1)						// wielomian zerowy
		os << 0;

	if (p.deg() == 0)					// wielomian stopnia 0
		os << p.getA(0);

	if (p.deg() == 1)                  // wielomian stopnia 1
    {
        os << p.getA(1) << "x ";

		if (p.getA(0) > 0)
			os << "+ " << p.getA(0);
		else if (p.getA(0) < 0)
			os << "- " << (-1) * p.getA(0);
	}

	else {
		os << p.getA(p.deg());
		os << "x^" << p.deg() << " ";

		if (p.deg() > 1)
        {
			for (int i = p.deg() - 1; i > 0; i--)
			{
				if (p.getA(i) > 0)
					os << "+ " << p.getA(i) << "x^" << i << " ";

				else if (p.getA(i) < 0)
					os << "- " << (-1)*p.getA(i) << "x^" << i << " ";

			}
		}

		if (p.getA(0) > 0)
			os << "+ " << p.getA(0);
		else if (p.getA(0) < 0)
			os << "- " << (-1) * p.getA(0);

	}

	return os;

}


int main() {

	Polynomial p1, p2;

	p1.setA(0, 1);
	p1.setA(1, 2);
	p1.setA(2, 1);

	p2.setA(0, 4);
	p2.setA(1, 3);
	p2.setA(2, 1);
    cout << "wielomian1 " << p1 <<endl;
	cout << "wielomian2 " << p2<< endl;
	cout << "Stopien1 " << p1.deg() << endl;
	cout << "Wartosc dla x=2 " << p1.v(2) << endl;
	cout << "Wielomiany sa " << ((p1 != p2) ? "rozne" : "rowne") << "." << endl;
	cout << "Suma " << p1 + p2 << endl;
	cout << "Roznica " << p1 - p2 << endl;
}

