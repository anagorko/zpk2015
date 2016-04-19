#include<iostream>
#include<vector>
using namespace std;

class Polynomial
{
    vector<double> a;

    double findRoot(double, double);

public:
    Polynomial(){
    };
//---------------------------------------------------
    double getA(int i) const{
    if(a.size() > i)
        return a[i];
    else
        return NULL;
    };
//---------------------------------------------------
    void setA(int i , double b){
    if(i < a.size())
        a[i] = b;
    else {
        a.resize(i+1, 0);
        a[i] = b;
    }
    };
//---------------------------------------------------
    int deg() const{
    for(int i = a.size() - 1; i >= 0 ; i--){
        if(a[i]!=0){
            return i;
            break;
        }
    }
    };
//---------------------------------------------------
    Polynomial& operator+=(const Polynomial &q);
    const Polynomial operator+(const Polynomial &q) const;

    Polynomial& operator*=(const Polynomial &q);
    const Polynomial operator*(const Polynomial &q) const;

    Polynomial& operator-=(const Polynomial &q);
    const Polynomial operator-(const Polynomial &q) const;

    bool operator==(const Polynomial &q) const;
    bool operator!=(const Polynomial &q) const;

    double v(double x) const;

    friend ostream& operator<<(ostream &os, const Polynomial &w);

    const Polynomial differential() const;

    vector<double> rationalRoots() const;
    vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);

int main(){
    Polynomial a;
    a.setA(0,1);
    a.setA(1,2);
    a.setA(2,1);
    cout << a.deg() << endl;
    a.setA(2,0);
    cout << a.deg() << endl;
}
