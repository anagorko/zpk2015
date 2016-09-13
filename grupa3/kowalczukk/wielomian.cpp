#include<iostream>
#include<vector>
using namespace std;

class Polynomial
{
	vector<double> a;

public:
	Polynomial();  

	double findRoot(double, double);    

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

};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R); 
const Polynomial gcd(const Polynomial &, const Polynomial &);  

double Polynomial::findRoot(double x1, double x2) 
{

	if (v(x1) == 0.0)
		return x1;
	if (v(x2) == 0.0)
		return x2;

	double srodek;

	while (x2 - x1 > 0.00001) 
	{
		srodek = (x1 + x2) / 2;
		if (v(srodek) == 0.0)
			return srodek;
		if (v(x1) * v(srodek) < 0)
			x2 = srodek;
		else
			x1 = srodek;
	}
	return (x1 + x2) / 2;
}

Polynomial::Polynomial() 
{
	a.push_back(0);
}

double Polynomial::getA(int miejsce) const 
{
	return a[miejsce];
}

void Polynomial::setA(int miejsce, double wsp) 
{
	a.resize(miejsce + 1, 0);
	a[miejsce] = wsp;
}

int Polynomial::deg() const 
{
	if (a.size() - 1)
		return a.size() - 1;
	else 
	{
		if (a[0])
			return 0;
		else
			return -1;
	}
}

Polynomial& Polynomial::operator+=(const Polynomial &q) 
{

	if (q.deg() > this->deg())
		this->a.resize(q.deg() + 1, 0);

	for (int i = 0; i <= q.deg(); i++)
		this->a[i] += q.getA(i);

	while (this->a[a.size() - 1] == 0 && a.size() > 1)	
		this->a.pop_back();

	return *this;

}

const Polynomial Polynomial::operator+(const Polynomial &q) const 
{
	return Polynomial(*this) += q;
}

Polynomial& Polynomial::operator*=(const Polynomial &q) 
{

	vector<double> x(this->deg() + q.deg() + 1, 0);

	for (int i = 0; i <= q.deg(); ++i)
		for (int j = 0; j <= this->deg(); ++j)
			x[i + j] += this->a[j] * q.getA(i);

	this->a = x;

	return *this;

}

const Polynomial Polynomial::operator*(const Polynomial &q) const
{
	return Polynomial(*this) *= q;
}

Polynomial& Polynomial::operator-=(const Polynomial &q) 
{

	if (q.deg() > this->deg())
		this->a.resize(q.deg(), 0);

	for (int i = 0; i <= q.deg(); i++)
		this->a[i] -= q.getA(i);

	while (this->a[a.size() - 1] == 0 && a.size() > 1)	
		this->a.pop_back();

	return *this;

}

const Polynomial Polynomial::operator-(const Polynomial &q) const 
{
	return Polynomial(*this) -= q;
}

bool Polynomial::operator==(const Polynomial &q) const 
{

	bool rowne = true;

	if (a.size() - 1 != q.deg())	
		rowne = false;
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
		rozne = true;
	else
		for (int i = a.size() - 1; i >= 0; i--)
			if (a[i] != q.getA(i))	
				rozne = true;

	return rozne;

}

double Polynomial::v(double x) const 
{

	double b = a[a.size() - 1];

	for (int i = a.size() - 2; i >= 0; i--) 
		b = a[i] + b * x;

	return b;

}

ostream& operator<<(ostream &os, const Polynomial &wiel) 
{

	if (wiel.deg() == -1)						
		os << 0;

	else if (wiel.deg() == 0)					
		os << wiel.getA(0);

	else if (wiel.deg() == 1) 
	{					
		if (wiel.getA(1) != 1)					
			os << wiel.getA(1);
		os << "x ";

		if (wiel.getA(0) > 0)
			os << "+ " << wiel.getA(0);
		else if (wiel.getA(0) < 0)
			os << "- " << (-1) * wiel.getA(0);
	}

	else
	{										
		if (wiel.getA(wiel.deg()) != 1)			
			os << wiel.getA(wiel.deg());
		os << "x^" << wiel.deg() << " ";

		if (wiel.deg() > 2)
		{
			for (int i = wiel.deg() - 1; i > 1; i--) 
			{
				if (wiel.getA(i) > 0) 
				{
					os << "+ ";
					if (wiel.getA(i) != 1)		
						os << wiel.getA(i);
					os << "x^" << i << " ";
				}

				else if (wiel.getA(i) < 0) 
				{
					os << "- ";
					if (wiel.getA(i) != -1)		
						os << (-1) * wiel.getA(i);
					os << "x^" << i << " ";
				}
			}
		}

		if (wiel.getA(1) > 0)
		{					
			os << "+ ";
			if (wiel.getA(1) != 1)
				os << wiel.getA(1);
			os << "x ";
		}
		else if (wiel.getA(1) < 0) 
		{
			os << "- ";
			if (wiel.getA(1) != -1)
				os << wiel.getA(1);
			os << "x ";
		}

		if (wiel.getA(0) > 0)					
			os << "+ " << wiel.getA(0);
		else if (wiel.getA(0) < 0)
			os << "- " << (-1) * wiel.getA(0);

	}

	return os;

}

const Polynomial Polynomial::differential() const 
{
	Polynomial wiel;
	if (a.size() > 1) 
	{
		for (int i = 1; i < a.size(); i++) 
		{
			if (a[i])
				wiel.setA(i - 1, a[i] * i);
		}
		return wiel;
	}
	else
		wiel.setA(0, 0);	
}

int main() 
{

	Polynomial w1, w2;

	w1.setA(0, 3);
	w1.setA(1, 4);
	w1.setA(2, 2);
	w1.setA(3, 2);

	w2.setA(0, 3);
	w2.setA(1, 2);
	w2.setA(2, 8);

	cout << "Wielomian w1 ma postac: " << w1 << endl;
	cout << "Stopien wielomianu w1 wynosi: " << w1.deg() << endl;
	cout << "Wartosc wielomianu w1 dla x = 1 wynosi: " << w1.v(1) << endl;
	cout << "Pochodna wielomianu w1 ma postac: " << w1.differential() << endl;
	cout << "Miejsce zerowe wielomianu w1 w przedziale (-10, 10) wynosi: " << w1.findRoot(-10, 10) << endl << endl;

	cout << "Wielomian w2 ma postac: " << w2 << endl;
	cout << "Stopien wielomianu w2 wynosi: " << w2.deg() << endl;
	cout << "Wartosc wielomianu w2 dla x = 1 wynosi: " << w2.v(1) << endl;
	cout << "Pochodna wielomianu w2 ma postac: " << w2.differential() << endl;
	cout << "Miejsce zerowe wielomianu w2 w przedziale (-10, 10) wynosi: " << w2.findRoot(-10, 10) << endl << endl;

	cout << "Wielomiany w1 i w2 sa " << ((w1 != w2) ? "rozne" : "rowne") << "." << endl;
	cout << "w1 + w2 = " << w1 + w2 << endl;
	cout << "w1 - w2 = " << w1 - w2 << endl;
	cout << "w1 * w2 = " << w1 * w2 << endl;
}
