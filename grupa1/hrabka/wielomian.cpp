#include <iostream>
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

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);


Polynomial::Polynomial()
{
    a = *(new vector<double>());
}

void Polynomial::setA(int position, double value)
{
    for(int i=a.size(); i<=position; i++)
    {
        a.push_back(0);
    }
    a.at(position) = value;
}

double Polynomial::getA(int position) const
{
    if(position >= a.size())
        return 0;
    return a.at(position);
}

int Polynomial::deg() const
{
    return a.size() - 1;
}

const Polynomial Polynomial::operator+(const Polynomial &q) const
{
    Polynomial result = *(new Polynomial());
    int max_deg = max(deg(), q.deg());
    for (int i=0; i<=max_deg; i++)
    {
        result.setA(i, getA(i) + q.getA(i));
    }
    return result;
}

const Polynomial Polynomial::operator-(const Polynomial &q) const
{
    Polynomial result = *(new Polynomial());
    int max_deg = max(deg(), q.deg());
    for (int i=0; i<=max_deg; i++)
    {
        result.setA(i, getA(i) - q.getA(i));
    }
    return result;
}

Polynomial& Polynomial::operator+=(const Polynomial&q)
{
    int max_deg = max(deg(), q.deg());
    for (int i=0; i<=max_deg; i++)
    {
        setA(i, getA(i) + q.getA(i));
    }
}

Polynomial& Polynomial::operator-=(const Polynomial&q)
{
    int max_deg = max(deg(), q.deg());
    for (int i=0; i<=max_deg; i++)
    {
       setA(i, getA(i) - q.getA(i));
    }
}

bool Polynomial::operator==(const Polynomial &q) const
{
    int max_deg = max(deg(), q.deg());
    for (int i=0; i<=max_deg; i++)
    {
      if(getA(i)!=q.getA(i)){
        return false;
      }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial &q) const
{
    return !((*this)==q);
}

double Polynomial::v(double x) const
{
    double sum = 0;
    double potega = 1;
    for(int i=0; i<a.size(); i++)
    {
        sum += a.at(i) * potega;
        potega *= x;
    }
    return sum;
}

const Polynomial Polynomial::differential() const
{
    Polynomial result = *(new Polynomial());
    for (int i=1; i<=deg(); i++)
    {
     result.setA(i-1, i * getA(i));
    }
    return result;
}

ostream& operator<<(ostream& os, const Polynomial& p)
{
    if(p.a.size() == 0)
        return os;
    for(int i=p.a.size() - 1; i>0; i--)
    {
        os<<p.a.at(i)<<"x^"<<i<<" + ";
    }
    os<<p.a.at(0);
    return os;
}

int main()
{
    cout<<"Wielomian"<<endl;
    Polynomial wielomian = *(new Polynomial());
    wielomian.setA(0, 2.5);
    wielomian.setA(1, 3);
    wielomian.setA(2, 1);
    cout<<wielomian<<endl;
    cout<<"Wartosc w 2: ";
    cout<<wielomian.v(2)<<endl;

    Polynomial wielomian2= *(new Polynomial());
    wielomian2.setA(0, 4.5);
    wielomian2.setA(1, 2);
    cout<<"Wielomian 2"<<endl;
    cout<<wielomian2<<endl;


    cout<<"Suma: ";
    cout<<wielomian+wielomian2<<endl;

    cout<<"Roznica: ";
    cout<<wielomian-wielomian2<<endl;

    cout<<"Suma +=: ";
    wielomian += wielomian2;
    cout<<wielomian<<endl;

    cout<<"Roznica -=: ";
    wielomian -= wielomian2;
    cout<<wielomian<<endl;

    cout<<"Rownosc: ";
    cout<<(wielomian==wielomian2)<<endl;
    cout<<(wielomian==wielomian)<<endl;

    cout<<"Nierownosc: ";
    cout<<(wielomian!=wielomian2)<<endl;

    cout<<"Pochodna: ";
    cout<<wielomian.differential()<<endl;
    return 0;
}
