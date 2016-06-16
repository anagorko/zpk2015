#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
class Polynomial
{
    vector<double> a;

public:
    Polynomial();

    double getA(int x) const
    {
        if(x >= a.size())
            return 0;
        else return a[x];
    }
    void setA(int x, double n)
    {
        if(a.size() <= x)
            a.resize(x+1);
        a[x] = n;
    }

    int deg() const
    {
        int d;
        for(int i=0;i<a.size();i++){
			if(a[i]==0){
			}else{
				d=i;
			}
		}
		return d;

    }

    Polynomial& operator+=(const Polynomial &q)
    {
        for (int i=0; i<=q.deg(); i++)
            setA(i, getA(i)+q.getA(i));

    }
    const Polynomial operator+(const Polynomial &q) const
    {
        Polynomial _a;
        for (int i=0; i<=q.deg(); i++)
            _a.setA(i, getA(i)+q.getA(i));
        return _a;
    }

    Polynomial& operator*=(const Polynomial &q)
    {
        Polynomial _a;
        for (int i = 0; i<=q.deg(); i++)
            for (int j = 0; j<=deg(); j++)
                _a.setA(i+j, _a.getA(i+j)+getA(j)*q.getA(i));
        for (int i=0; i<_a.deg(); i++)
            setA(i, _a.getA(i));
    }
    const Polynomial operator*(const Polynomial &q) const
    {
        Polynomial _a;
        for (int i = 0; i<=q.deg(); i++)
            for (int j = 0; j<=deg(); j++)
                _a.setA(i+j, _a.getA(i+j)+getA(j)*q.getA(i));
        return _a;
    }
    Polynomial& operator-=(const Polynomial &q)
    {
        for (int i=0; i<=q.deg(); i++)
            setA(i, getA(i)-q.getA(i));
    }
    const Polynomial operator-(const Polynomial &q) const
    {
        Polynomial _a;
        for (int i=0; i<=q.deg(); i++)
            _a.setA(i, getA(i)-q.getA(i));
        return _a;
    }

    bool operator==(const Polynomial &q) const
    {
        if(deg()!= q.deg())
            return false;
        for (int i=0; i<=deg(); i++)
            if(a[i]!= q.getA(i))
                return false;
        return true;
    }
    bool operator!=(const Polynomial &q) const
    {
        if(deg()!= q.deg())
            return true;
        for (int i=0; i<=deg(); i++)
            if(a[i]!= q.getA(i))
                return true;
        return false;
    }

    double v(double x) const
    {
        double w = 0;
        for (int i=1; i<=deg(); i++)
            w += a[i]*pow(x, i);
        w+=a[0];
        return w;
    }

    friend ostream& operator<<(ostream& ostr, const Polynomial& q)
    {
        bool x;
        for(int i=q.deg(); i>0 ;i--)
        {
            if(q.getA(i)!=0){
                if(q.getA(i)==-1)
                    ostr<<"-";
                else if(q.getA(i)>0 && x)
                    ostr<<"+"<<q.getA(i);
                else
                    ostr<<q.getA(i);
                ostr<<"x^"<<i;
                if(!x)
                    x=true;
            }
        }
    }

};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R)
{
    R = W;
    for(int i=R.deg(); R.deg()>=P.deg() && i>=0; i--)
    {
        Q.setA(i-P.deg(), R.getA(i)/P.getA(P.deg()));
        for(int j=P.deg(); j>=0; j--){
            R.setA((i-P.deg())+j, R.getA((i-P.deg())+j)-( P.getA(j) * Q.getA(i-P.deg()) ) );
        }
    }
}
const Polynomial gcd(const Polynomial &, const Polynomial &);


int main()
{
    return 0;
}
