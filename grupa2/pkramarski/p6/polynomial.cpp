#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Polynomial
{
    vector<double> a;

    double findRoot(double, double);

public:
    Polynomial(){
        a.push_back(0);
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
        return 0;
    };
//---------------------------------------------------
    Polynomial& operator+=(const Polynomial &q){
        int max_deg = max(deg(),q.deg());
        for(int i = 0; i <= max_deg;i++){
            setA(i,getA(i) + q.getA(i));
        }
        return *this;
    };
//---------------------------------------------------
    const Polynomial operator+(const Polynomial &q) const{
        Polynomial p = *this;
        p += q;
        return p;
    };
//---------------------------------------------------
    Polynomial& operator*=(const Polynomial &q){
        vector<double> b(deg()+q.deg()+1,0);
        for(int i = 0;i <= deg();i++)
            for(int j = 0;j <= q.deg();j++)
                b[i+j] += getA(i) * q.getA(j);
        a = b;
        return *this;
    };
//---------------------------------------------------
    const Polynomial operator*(const Polynomial &q) const{
        Polynomial p = *this;
        p *= q;
        return p;
    };
//---------------------------------------------------
    Polynomial& operator-=(const Polynomial &q){
    int max_deg = max(deg(),q.deg());
        for(int i = 0; i <= max_deg;i++){
            setA(i,getA(i) - q.getA(i));
        }
        return *this;
    };
//---------------------------------------------------
    const Polynomial operator-(const Polynomial &q) const{
        Polynomial p = *this;
        p -= q;
        return p;
    };
//---------------------------------------------------
    bool operator==(const Polynomial &q) const{
        bool czyrowne = true;
        if(deg() == q.deg()){
            for(int i = 0; i <= deg(); i++)
                if(getA(i) != q.getA(i)){
                    czyrowne = false;
                    break;
            }
        }
        else
            czyrowne = false;
        return czyrowne;
    };
//---------------------------------------------------
    bool operator!=(const Polynomial &q) const{
        return !(*this == q);
    };
//---------------------------------------------------
    double v(double x) const{
        double value = 0;
        for(int i = deg();i >= 0;i--)
            value = value*x + getA(i);
        return value;
    };
//---------------------------------------------------
    friend ostream& operator<<(ostream &os, const Polynomial &w){
        for(int i = w.deg();i >= 0;i--){
            if(w.deg() == 0)
                os << w.getA(i);
            else if(w.deg() == 1){
                if(i==w.deg() && w.getA(i)!=1 && w.getA(i)!=-1)
                    os << w.getA(i) << "x";
                else if(i==w.deg() && (w.getA(i)==1))
                    os << "x";
                else if(i==w.deg() && (w.getA(i)==-1))
                    os << "-x";
                else if(i==0 && w.getA(i)>0)
                    os << "+" << w.getA(i);
                else if(i==0 && w.getA(i)<0)
                    os << w.getA(i);
                }
            else if(w.deg()>1){
                if(i==w.deg()){
                    if(w.getA(i)!=1 && w.getA(i)!=-1)
                        os << w.getA(i) << "x^" << i;
                    else if(w.getA(i)==1)
                        os << "x^" << i;
                    else if(w.getA(i)==-1)
                        os << "-x^" << i;
                }
                else if(i<w.deg()){
                    if(i>1 && w.getA(i)>0 && w.getA(i)!=1)
                        os << "+" << w.getA(i) << "x^" << i;
                    else if(i>1 && w.getA(i)>0 && w.getA(i)==1)
                        os  << "+x^" << i;
                    else if(i==1 && w.getA(i)>0 && w.getA(i)!=1)
                        os << "+" << w.getA(i) << "x";
                    else if(i==1 && w.getA(i)>0 && w.getA(i)==1)
                        os << "+x";
                    else if(i==0 && w.getA(i)>0)
                        os << "+" << w.getA(i);

                    else if(i>1 && w.getA(i)<0 && w.getA(i)!=-1)
                        os << w.getA(i) << "x^" << i;
                    else if(i>1 && w.getA(i)<0 && w.getA(i)==-1)
                        os  << "-x^" << i;
                    else if(i==1 && w.getA(i)<0 && w.getA(i)!=-1)
                        os << w.getA(i) << "x";
                    else if(i==1 && w.getA(i)<0 && w.getA(i)==-1)
                        os << "-x";
                    else if(i==0 && w.getA(i)<0)
                        os << w.getA(i);
                }
            }
        }
        return os;
    };
//---------------------------------------------------
    const Polynomial differential() const{
        Polynomial d;
        for(int i = 0;i < deg();i++)
            d.setA(i,(i+1) * getA(i+1));
        return d;
    };
//---------------------------------------------------
    vector<double> rationalRoots() const{
        vector<double> roots;
            if(deg()==0 && getA(0) == 0)
                roots.push_back(0);
            else if(deg()==1){
                roots.push_back(-getA(0)/getA(1));
            }
            else if(deg()>1){
                for(double p = abs(getA(0));p > 0;p--){
                    for(double q = abs(getA(deg()));q > 0;q--){
                        if(v(p/q)==0)
                            roots.push_back((p/q));
                        if(v(-p/q)==0)
                            roots.push_back((-p/q));
                    }
                }
            }
        vector<double> rootsFINAL;
            for(int i = 0;i < roots.size();i++){
                bool dedup = true;
                for(int j = i + 1;j < roots.size();j++){
                    if(roots[i] == roots[j]){
                        dedup = false;
                }
            }
                if(dedup == true)
                    rootsFINAL.push_back(roots[i]);
        }
        return rootsFINAL;
    };
//---------------------------------------------------
    vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R){
    if(W.deg() < P.deg()){
        R = W;
    }
    else {
        Polynomial ZERO;
        Polynomial WW = W;
        Polynomial S;
        while(WW.deg() >= P.deg() && WW != ZERO){
            S.setA(WW.deg()-P.deg(),WW.getA(WW.deg()) / P.getA(P.deg()));
            Q += S;
            int WWdeg = WW.deg();
            WW -= P * S;
            S.setA(WWdeg-P.deg(),0);
        }
        R = W - (P * Q);
    }
};
//---------------------------------------------------
const Polynomial gcd(const Polynomial &P, const Polynomial &Q){
    Polynomial ZERO;
    Polynomial PP = P;
    Polynomial QQ = Q;
    Polynomial R;
    while(QQ != ZERO){
        Polynomial S;
        div(PP,QQ,S,R);
        PP = QQ;
        QQ = R;
    }
    return PP;
};
//---------------------------------------------------
int main(){
    Polynomial a, b;

    a.setA(0,6);
    a.setA(1,-5);
    a.setA(2,1);
    b.setA(0,-3);
    b.setA(1,1);

    cout << "Wielomian A: " << a << endl;
    cout << "Wielomian B: " << b << endl;
    cout << endl;
    cout << "Stopien wielomianu A: " << a.deg() << endl;
    cout << "Stopien wielomianu B: " << b.deg() << endl;
    cout << endl;
    cout << "Suma wielomianow A i B: " << a + b << endl;
    cout << endl;
    cout << "Roznica wielomianow A i B: " << a - b << endl;
    cout << endl;
    cout << "Iloczyn wielomianow A i B: " << a * b << endl;
    cout << endl;
    cout << "Czy wielomian A jest rowny B: ";
    if (a == b)
        cout << "TAK"<< endl;
    else
        cout << "NIE"<< endl;
    cout << endl;
    cout << "Czy wielomian A jest rozny od B: ";
    if (a != b)
        cout << "TAK"<< endl;
    else
        cout << "NIE"<< endl;
    cout << endl;
    cout << "Pochodna wielomianu A: " << a.differential() << endl;
    cout << "Pochodna wielomianu B: " << b.differential() << endl;
    cout << endl;
    cout << "Wartosc wielomianu A w punkcie x = 1: " << a.v(1) << endl;
    cout << "Wartosc wielomianu B w punkcie x = 1: " << b.v(1) << endl;
    cout << endl;
    cout << "NWD wielomianow A i B: " << gcd(a,b) << endl;
}
