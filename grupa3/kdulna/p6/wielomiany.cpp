#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
using namespace std;

class Polynomial
{
    vector<double> a;

    double findRoot(double s, double t){
        double p = s, q = t;
        if (v(p) == 0){
            return p;
        }
        if (v(q) == 0){
            return q;
        }
        if ((v(q) > 0 && v(p) > 0) || (v(q) < 0 && v(p) < 0)){
            cout << "Nie wiadomo, czy istnieje pierwiastek w zadanym przedziale [" << s << " , " << t << "]." << endl;
            return 0;
        }
        while (abs(p - q) > 0.000001){
            if (v(q) < 0 && v(p) > 0){
                double r = (p + q)/2;
                if (v(r) > 0){
                    p = r;
                }
                else if (v(r) < 0){
                    q = r;
                }
                else{
                    return r;
                }
            }
            else if (v(q) > 0 && v(p) < 0){
                double r = (p + q)/2;
                if (v(r) > 0){
                    q = r;
                }
                else if (v(r) < 0){
                    p = r;
                }
                else{
                    return r;
                }
            }
        }
        return (p + q)/2;
    }


public:
    Polynomial(){
        vector<double> a(1,0);
    }
    Polynomial(vector<double> b){
        a = b;
    }

    double getA(int d) const{
        if (d < a.size()){
            return a[d];
        }
        else{
            return 0;
        }
    }
    void setA(int d, double w){
        if (a.size() < d+1){
        a.resize(d+1);
        }
        a[d] = w;
    }

    int deg() const{
        for (int i = a.size() - 1; i >= 0; --i){
            if (getA(i) != 0){
                return i;
                break;
            }
        }
        return -1;
    }

    int najmn() const{
        if (deg() == -1){
            return 0;
        }
        for (int i = 0; i <= deg(); ++i){
            if (getA(i) != 0){
                return i;
            }
        }
    }

    Polynomial& operator+=(const Polynomial &q){
        int st = max(deg(), q.deg());
        for (int i = 0; i <= st ; ++i){
            setA(i, getA(i) + q.getA(i));
        }
        return *this;
    }
    const Polynomial operator+(const Polynomial &q) const{
        Polynomial r(a);
        r += q;
        return r;
    }

    Polynomial& operator-=(const Polynomial &q){
        int st = max(deg(), q.deg());
        for (int i = 0; i <= st ; ++i){
            setA(i, getA(i) - q.getA(i));
        }
        return *this;
    }
    const Polynomial operator-(const Polynomial &q) const{
        Polynomial r(a);
        r -= q;
        return r;
    }

    Polynomial& operator*=(const Polynomial &q){
        int st = deg() + q.deg();
        vector<double> b(st + 1, 0);
        Polynomial r(b);
        for (int i = 0; i <= st ; ++i){
            for (int j = 0; j <= i; ++j){
                r.setA(i, r.getA(i) + getA(j) * q.getA(i-j));
            }
        }
        for (int i = 0; i <= st ; ++i){
            setA(i, r.getA(i));
        }
        return *this;
    }
    const Polynomial operator*(const Polynomial &q) const{
        Polynomial r(a);
        r *= q;
        return r;
    }

    bool operator==(const Polynomial &q) const{
        if (deg() != q.deg()){
            return false;
        }
        else for (int i = 0; i <= deg(); ++i){
            if (getA(i)!= q.getA(i)){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Polynomial &q) const{
        return !(*this == q);
    }

    double v(double x) const{
        int st = deg();
        double w = 0;
        for (int i = st; i >= 0; --i){
            w = w * x + getA(i);
        }
        return w;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& p){
        if (p.deg() == -1){
            os << 0;
        }
        if (p.getA(0) != 0){
            if (p.getA(0) > 0){
                os << p.getA(0) << " ";
            }
            else{
                os << "- " << abs(p.getA(0)) << " ";
            }
        }
        if (p.getA(1) == 1 && p.getA(0) == 0){
            os << "x ";
        }
        else if (p.getA(1) == 1 && p.getA(0) != 0){
            os << "+ x ";
        }
        else if (p.getA(1) == -1){
            os << "- x ";
        }
        else if (p.getA(1) != 0){
            if (p.getA(0) != 0){
                if (p.getA(1) > 0){
                    os << "+ " << p.getA(1) << " * x ";
                }
                else if(p.getA(1) < 0){
                    os << "- " << abs(p.getA(1)) << " * x ";
                }
            }
            else if (p.getA(1) > 0){
               os << p.getA(1) << " * x ";
            }
            else if (p.getA(1) < 0){
               os << "- " << abs(p.getA(1)) << " * x ";
            }
        }
        for (int i = 2; i <= p.deg(); ++i){
            if (p.getA(i) != 0 && i != p.najmn()){
                if (p.getA(i) == 1){
                    os << "+ x ^ " << i << " ";
                }
                else if (p.getA(i) == -1){
                    os << "- x ^ " << i << " ";
                }
                else if (p.getA(i) > 0){
                    os << "+ " << p.getA(i) << " * x ^ " << i << " ";
                }
                else if (p.getA(i) < 0){
                    os << "- " << abs(p.getA(i)) << " * x ^ " << i << " ";
                }
            }
            else if (p.getA(i) != 0){
                if (p.getA(1) == 1){
                    os << "x ^ " << i << " ";
                }
                else if (p.getA(1) == -1){
                    os << "- x ^ " << i << " ";
                }
                else if (p.getA(i) > 0){
                    os << p.getA(i) << " * x ^ " << i << " ";
                }
                else if (p.getA(i) < 0){
                    os << "- " << abs(p.getA(i)) << " * x ^ " << i << " ";
                }
            }
        }
        os << endl;
        return os;
    }

    const Polynomial differential() const{
        vector<double> h(deg());
        Polynomial q(h);
        for (int i = 0; i < deg(); ++i){
            q.setA(i, (i + 1) * getA(i + 1));
        }
        return q;
    }

    vector<double> realRoots() const{
        vector<double> r;
        Polynomial D = *this;
        if (D.deg() == -1){
            cout << "Kazda liczba x jest pierwiastkiem wielomianu zerowego. Przykladowy pierwiastek calkowity to:" << endl;
            r.push_back(rand());
            return r;
        }
        else if (D.deg() == 0){
            cout << "Wielomian staly niezerowy nie ma pierwiastkow." << endl;
            return r;
        }
        else if (D.deg() == 1){
            r.push_back(-getA(0)/getA(1));
            return r;
        }
        else if (D.deg() > 1){
            Polynomial E = D.differential();
            r = E.realRoots();
            vector<double> s;
            for(int i = 0; i < r.size() + 1; ++i){
                if (i == 0) {
                    if (D.v(r[0]) > 0 && E.v(r[0] - 1) > 0){
                        int j = 1;
                        while (!(D.v(r[0] - j) < 0)){
                            ++j;
                        }
                        s.push_back(D.findRoot(r[0] - j, r[0]));
                    }
                    else if ((D.v(r[0]) < 0 && E.v(r[0] - 1) < 0)){
                        int j = 1;
                        while (!(D.v(r[0] - j) > 0)){
                            ++j;
                        }
                        s.push_back(D.findRoot(r[0] - j, r[0]));
                    }
                    else if (D.v(r[0]) < 0 && D.v(r[0]) > 0){
                        s.push_back(r[0]);
                    }
                }
                if (i < r.size() && i > 0){
                    if ((D.v(r[i - 1]) >= 0 && D.v(r[i]) <= 0) || (D.v(r[i - 1]) <= 0 && D.v(r[i]) >= 0)){
                        s.push_back(D.findRoot(r[i - 1], r[i]));
                    }
                }
                if (i == r.size()){
                    if (D.v(r[i - 1]) > 0 && E.v(r[i - 1] + 1) < 0){
                        int j = 1;
                        while (!(D.v(r[i - 1] + j) < 0)){
                            ++j;
                        }
                        s.push_back(D.findRoot(r[i - 1] + j, r[i - 1]));
                    }
                    else if ((D.v(r[i - 1]) < 0 && E.v(r[i - 1] + 1) > 0)){
                        int j = 1;
                        while (!(D.v(r[i - 1] + j) > 0)){
                            ++j;
                        }
                        s.push_back(D.findRoot(r[i - 1] + j, r[i - 1]));
                    }
                    else if (D.v(r[0]) == 0 && D.v(r[0]) > 0){
                        s.push_back(r[0]);
                    }
                }
            }
            int n = s.size();
            vector<double> t;
            bool pom = true;
            for (int i = 0; i < n; ++i){
                for (int j = i + 1; j < n; ++j){
                    pom = pom * (s[i] != s[j]);
                }
                if (pom){
                    t.push_back(s[i]);
                }
            }
            return t;
        }
    }
    vector<double> rationalRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R){
    if (W.deg() < P.deg()){
        R = W;
    }
    else{
        Polynomial V = W;
        Polynomial S;
        while (V.deg() >= P.deg()){
            S.setA(V.deg() - P.deg(), V.getA(V.deg()) / P.getA(P.deg()));
            Q += S;
            int dg = V.deg();
            V -= S * P;
            S.setA(dg - P.deg(), 0);
        }
        R = W - (P * Q);
    }
}

const Polynomial gcd(const Polynomial &P, const Polynomial &Q){
    Polynomial S, R;
    Polynomial PP = P;
    Polynomial QQ = Q;
    vector<double> zero;
    while (QQ.deg() != -1){
        for (int i = 0; i <= S.deg(); ++i){
            S.setA(i, 0);
        }
        div(PP, QQ, S, R);
        PP = QQ;
        QQ = R;
    }
    return PP;
}
