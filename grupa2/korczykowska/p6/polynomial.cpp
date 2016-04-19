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

double Polynomial::getA(int i) const {
	return a[i];
}

void Polynomial::setA(int i, double w) {
	a[i] = w;
}

int Polunomial::deg(){
    if (a.size()==1 && a[0]==0)
        return -1; /*stopień wielomianu zerowego = -1*/
    else
        return a.size()-1;

}


Polynomial & Polynomial::operator+=(const Polynomial &q){
        if (q.deg()>deg()) /*zwiekszy sie stopien wielomianu a*/
            a.resize(q.deg+1-(deg()+1),0);
            for (int l = 0; l <= q.deg()+1; ++l)
                a[l]+=q.getA(l);

        else
            for (int l = 0; l <= q.deg()+1; ++l)
                a[l]+=q.getA(l);

	return *this;
}


const Polynomial Polynomial::operator+(const Polynomial &q) const;{
    return Polynomial(*this) += q;
}


Polynomial & Polynomial::operator*=(const Polynomial &q){
            a.resize(q.deg()+deg(),0);

    /*wektor pomoconiczy*/
    vector<double> pom(q.deg()+deg()-1,0);

        for (int i=0; i<=pom.size();i++)
          {

              for (int j=0;j<=i; j++)
              {
                  pom[i]+=q.getA(j)*getA(i-j);
              }
          }
          return pom;

    a=pom;
	return *this;
}


const Polynomial Polynomial::operator*(const Polynomial &q) const;{
    return Polynomial(*this) *= q;
}


Polynomial & Polynomial::operator-=(const Polynomial &q){
        if (q.deg()>deg()) /*zwiekszy sie stopien wielomianu a*/
            a.resize(q.deg+1-(deg()+1),0);
            for (int l = 0; l <= q.deg()+1; ++l)
                a[l]+=q.getA(l);

        else
            for (int l = 0; l <= q.deg()+1; ++l)
                a[l]-=q.getA(l);

	return *this;
}


const Polynomial Polynomial::operator-(const Polynomial &q) const;{
    return Polynomial(*this) -= q;
}

bool Polynomial::operator==(const Polynomial &q) const;{
    if (deg() != q.deg())
        return false;
    else if {
       for(i=0; i<=q.deg(); ++i)
                if a[i] != q.getA[i]{
                    return false;
                    break;}
        }
    else
        return true;
}

bool Polynomial::operator!=(const Polynomial &q) const;{
    if (deg() != q.deg())
        return true;
    else if {
       for(i=0; i<=q.deg(); ++i)
                if a[i] != q.getA[i]{
                    return true;
                    break;}
        }
    else
        return false;
}

double Polynomial::v(double x) const;{
    if deg()=0
        return a[0];
    else {
        double wartosc = a[deg()+1];
            for(i = 1; i<=deg(); i++){
                wartosc=wartosc * x + a[deg()+1-i];
        }
    }
}


void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);
