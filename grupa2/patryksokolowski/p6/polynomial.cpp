#include<iostream>
#include <string>
#include <vector>
using namespace std;

class Polynomial
{
    vector<double> a;

    double findRoot(double, double);

public:
    Polynomial(){
        a.resize(1,0);
    }
    double getA(int i) const{
        if (i>=a.size()) return 0;
        return a[i];
    }
    void setA(int i, double x){
        if (i>=a.size()){
            a.resize(i+1,0);
            a[i] = x;
        }
        else a[i] = x;
    }

    int deg() const{
        int i = a.size()-1;
        while (a[i]==0){
            i--;
        }
        if (i==-1) return 0;
        return i;
    };

    Polynomial& operator+=(const Polynomial &q){
        if (deg()>q.deg()){
            for (int i=0;i<=q.deg();i++){
                a[i]+= q.getA(i);
            }
        }
        else {
            a.resize(q.deg()+1,0);
            for (int i=0;i<=q.deg();i++){
                a[i]+= q.getA(i);
            }
        }
    return *this;
    int i = a.size()-1;
    while(a[i]!=0){
        a.pop_back();
        i--;
    }
    if (deg()==-1) setA(0,0);
    }
    const Polynomial operator+(const Polynomial &q) const{
        return Polynomial(*this)+= q;
    }

    Polynomial& operator*=(const Polynomial &q){
        vector <double> wynik(a.size()+q.deg(),0);
        for (int i=0;i<a.size();i++){
            for (int j=0;j<=q.deg();j++){
                wynik[i+j] += a[i] * q.getA(i);
            }
        }
        a = wynik;
        return *this;
    }
    const Polynomial operator*(const Polynomial &q) const{
        return Polynomial(*this)*= q;
    }

    Polynomial& operator-=(const Polynomial &q){
    if (deg()>q.deg()){
            for (int i=0;i<=q.deg();i++){
                a[i]-= q.getA(i);
            }
        }
        else {
            a.resize(q.deg()+1,0);
            for (int i=0;i<=q.deg();i++){
                a[i]-= q.getA(i);
            }
        }
    return *this;
    int i = a.size()-1;
    while(a[i]!=0){
        a.pop_back();
        i--;
    }
    if (deg()==-1) setA(0,0);
    }
    const Polynomial operator-(const Polynomial &q) const{
        return Polynomial(*this)-= q;
    }

    bool operator==(const Polynomial &q) const {
        if(deg()!=q.deg()) return false;
        for (int i=0;i<=deg();i++){
            if (a[i]!=q.getA(i)) return false;
        }
        return true;
    }
    bool operator!=(const Polynomial &q) const {
        if (Polynomial(*this)==q) return false;
        return true;
    };

    double v(double x) const{
        double wynik = a[0];
        for (int i=1;i<=deg();i++){
            wynik = wynik * x + a[i];
        }
    return wynik;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& q){
    bool poczatek = true;
        for (int i=q.deg();i>=0;i--){
            if (q.getA(i)!=0 && i!=0){
                if (q.getA(i)==-1){
                    if (i!=1) cout << "-x^" << i;
                    else cout << "-x";
                }
                if (q.getA(i)==1){
                    if (poczatek){
                        if (i!=1) cout << "x^" << i;
                        else cout << "x";
                        poczatek = false;
                    }
                    else {
                        if (i!=1) cout << "+x^" << i;
                        else cout << "+x";
                    }
                }
                if (q.getA(i)<0 && q.getA(i)!=-1){
                    if (i!=1) cout << q.getA(i) << "x^" << i;
                    else cout << q.getA(i) << "x";
                }
                if (q.getA(i)>0 && q.getA(i)!=1) {
                    if (poczatek){
                        if (i!=1) cout << q.getA(i) <<"x^" << i;
                        else cout << q.getA(i) <<"x";
                        poczatek = false;
                    }
                    else {
                        if (i!=1) cout << "+" << q.getA(i) << "x^" << i;
                        else cout << "+" << q.getA(i) << "x";
                    }
                }
            }
            if (i==0 && q.getA(i)!=0){
                if (q.getA(i)>0){
                    if (poczatek){
                    cout << q.getA(i);
                    poczatek = false;
                    }
                    else {
                        cout << "+" << q.getA(i);
                    }
                }
                if (q.getA(i)<0){
                    cout << q.getA(i);
                }
            }
        }
        if (q.deg()==0 && q.getA(0)==0){
            cout << 0;
        }
    return os;
    }

    const Polynomial differential() const{
        Polynomial diff;
        diff.a.resize(deg()-1,0);
        for (int i=0;i<deg();i++) {
            diff.setA(i,a[i+1]*(i+1));
        }
        return diff;
    }

    vector<double> rationalRoots() const;
    vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);

// niestety nie zdazylem zaimplementowac funkcji div oraz gcd w terminie, dodam w najblizszym czasie

int main() {
}
