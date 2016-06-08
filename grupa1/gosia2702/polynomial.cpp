#include<iostream>
#include <vector>

using namespace std;

class Polynomial{
  
    vector<double> a;
    
    double findRoot(double pocz, double kon) {
        double p = pocz;
        double k = kon;
        double vp = v(p);
        double vk = v(k);
        double s;
        if(vp==0)
            return p;
        if(vk==0)
            return k;
        
        if ((vp>0 && vk>0) || (vp<0 && vk<0)) {
            cout << "Tą metodą nie da się odszukać pierwiastków w przedziale - nie ma pewności, że istnieją";
            return 0;
        }
        
        while (k-p >0.00001) {
            s = (k+p)/2;
            if v(s)==0
                return s;
            if ((v(s)>0 && v(p)> 0) || (v(s)<0 && v(p)<0))
                p=s;
            else
                q=s;
            
        }
    
        return (k+p)/2;
    }

public:
    Polynomial() {};

    double getA(int n) const{
        if (n>a.size())
            return 0;
        else 
            return a[i];
    }
    void setA(int n, double war) {
        if (a.size() > n)
            a[n]=war;
        else 
        {
            a.resize(n+1,0);
            a[n]=war;
        }
    }
    int deg() const {
    //Ktos mógl wpisywac zera i chciałbym to wyłapać, więc nie będę posługiwał się tylko wartością a.size(), ale sprawdze czy to nie są zera
        for(int i=a.size(); i>=0; i--) {
            if(a[i]!=0)
                return i;
        }
        return 0; //to bedzie oznaczac, ze wielomian pusty, zerowy
    }

    Polynomial& operator+=(const Polynomial &q) {
        int ten = this->deg();
        for(int i=0; i<=q.deg();i++) {
            if( i<=ten)
                this->setA(i,this->getA(i) + q.getA(i));
            else
                this->setA(i,q.getA(i));
        }
        return *this;
    }
    const Polynomial operator+(const Polynomial &q) const {
        Polynomial* dodaj = new Polynomial;
        for (int i =0; i<= max(this->deg(),q.deg());i++) {
            dodaj->setA(i,this->getA(i)+q.getA(i));
        }
        return *dodaj;
    }

    Polynomial& operator*=(const Polynomial &q) {
        Polynomial mnozenie();
        For (int i =0; i< this->deg()+ q.deg();i++){
            for (int j =0; j<i+1;j++) {
                mnozenie.setA(i,mnozenie.getA(i)+this->getA(j)*q.getA(i-j));
            }
        }
        For (int i =0; i< this->deg()+ q.deg();i++){
            this->setA(i,mnozenie.getA(i));
        }
        return *this;
    }
    const Polynomial operator*(const Polynomial &q) const {
        Polynomial* mnozenie = new Polynomial;
        For (int i =0; i< this->deg()+ q.deg();i++){
            for (int j =0; j<i+1;j++) {
                mnozenie->setA(i,mnozenie->getA(i)+this->getA(j)*q.getA(i-j));
            }
        }
        return *mnozenie;
    }

    Polynomial& operator-=(const Polynomial &q){
        int ten = this->deg();
        for(int i=0; i<=q.deg();i++) {
            if( i<=ten)
                this->setA(i,this->getA(i) - q.getA(i));
            else
                this->setA(i,-q.getA(i));
        }
        return *this;
    }
    const Polynomial operator-(const Polynomial &q) const {
        Polynomial* odejmij = new Polynomial;
        for (int i =0; i<= max(this->deg(),q.deg());i++) {
            odejmij->setA(i,this->getA(i)-q.getA(i));       //Zakładam, że jeżeli wielomian jest mniejszego rzedu to posiada same zera.
        }
        return *odejmij;    
    }

    bool operator==(const Polynomial &q) const {
        for (int i =0; i<= max(this->deg(),q.deg());i++) {
            if(this->getA(i)!= q.getA(i))
                return false;
        }
        return true;
    }
    bool operator!=(const Polynomial &q) const {
        return !(*this == q);
    }

    double v(double x) const{
        double wynik = 0;
        for (i=0;i<= this->deg();i++) {
            wynik = wynik + x* this->getA(i);
        }
    return wynik;
    }


//Te fragmenty sa zakodowane, poniewaz nie uzupełniono ich kodu
//    friend ostream& operator<<(ostream&, const Polynomial&);

//  const Polynomial differential() const;

//   vector<double> rationalRoots() const;
//   vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);
};
