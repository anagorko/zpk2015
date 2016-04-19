#include <iostream>
#include <vector>
using namespace std;

class Polynomial
{
    vector<double> a;
public:
double findRoot(double x, double y)
    {
        if (v(x)*v(y)>0) {cout<<"wartosc wielomianu w tych punktach ma taki sam znak " ;}
        while (v((x+y)/2)>0.0001 | v((x+y)/2)<-0.0001){
                if (v((x+y)/2)*v((x))<0) {y=(x+y)/2; }
                else {x=(x+y)/2; }
        }
        return (x+y)/2;
    }


    Polynomial(){}
    Polynomial(vector<double> _a)
    {
        a=_a;
    }

    ~Polynomial(){}

    double getA(int i) const
    {
        if (a.size() < i) { //cout << "zly wyspolczynnik" << endl;
                            return 0;}
        else  return a[i];

    }
    void setA(int i, double x)
    {
        if (a.size() < i) {a.resize(i+1,0);}
        a[i] = x;
       // cout<< "ustalono "<< a[i]<< " przy x^" <<i<<endl;

    }

    int deg() const
    {   int i = a.size();
        while (a[i-1] == 0)
              {i = i - 1;}
        return i-1;
    }

    Polynomial& operator+=(const Polynomial &q)
    {

        for(int i=0; i<=max(deg(), q.deg()); i++)
        {
            setA(i,getA(i)+q.getA(i));
        }

    }

    const Polynomial operator+(const Polynomial &q) const
    {
        Polynomial w;
        int k=max(deg(), q.deg());
        w.setA(k,0);

        for(int i=0; i<=k; i++)
            {
                w.setA(i,getA(i)+q.getA(i));
            }
        return w;

    }

    Polynomial& operator*=(const Polynomial &q)
    {
        Polynomial u;
        int k=(deg()+q.deg());
        u.setA(k,0);

        double w=0;
        int i=0;
        int j=0;
         for(i=0; i<=deg(); i++)
        {
            for( j=0; j<=q.deg(); j++) {

            u.setA(i+j,u.getA(i+j)+getA(i)*q.getA(j)) ;

            }
            j=0;

        }

         for(i=0; i<=k; i++)
            {
                setA(i,u.getA(i));
            }
    }

    const Polynomial operator*(const Polynomial &q) const
    {
        Polynomial u;
        int k=(deg()+q.deg());
        u.setA(k,0);

        double w=0;
        int i=0;
        int j=0;
         for(i=0; i<=deg(); i++)
        {
            for( j=0; j<=q.deg(); j++) {

            u.setA(i+j,u.getA(i+j)+getA(i)*q.getA(j)) ;

            }
            j=0;

        }
       return u;
    }

    Polynomial& operator-=(const Polynomial &q)
    {

        for(int i=0; i<=max(deg(), q.deg()); i++)
        {
            setA(i,getA(i)-q.getA(i));
        }

    }

    const Polynomial operator-(const Polynomial &q) const
    {
        Polynomial w;
        int k=max(deg(), q.deg());
        w.setA(k,0);

        for(int i=0; i<=k; i++)
            {
                w.setA(i,getA(i)-q.getA(i));
            }
        return w;

    }

    bool operator==(const Polynomial &q) const{
        if (deg()!=q.deg()) {return false;}

        for(int i=1; i<= deg(); i++)
        {
            if (getA(i)!=q.getA(i))  return false;
        }
        return true;

    }
    bool operator!=(const Polynomial &q) const {
        if (deg()==q.deg()) {return false;}

        for(int i=1; i<= deg(); i++)
        {
            if (getA(i)==q.getA(i))  return false;
        }
        return true;

    }

    double v(double x) const
    {
        double w=a[a.size()];
        for (int i=a.size()-1; i>=0;i--)
           {
            w=w*x+a[i];
            }
        return w;
    }

    friend ostream& operator<<(ostream& o, const Polynomial& p)
    {
        //o<<"W(x) = ";
       for(int i=p.deg(); i>=2; i--){
            if (p.getA(i)!=0) {
        o<<p.getA(i)<<"*x^"<<i;
           if (p.getA(i-1)>0 & i>=3) {o<<" + ";} }
        }
     if (p.deg()>1){
         if (p.getA(1)>0 & p.getA(1)!=1 ) o<<" + "<<p.getA(1)<<"*x";
         if (p.getA(1)<0) o<<p.getA(1)<<"*x";
         if (p.getA(1)==1) o<<" + "<<"x";}
     else {  if (p.getA(1)>0 & p.getA(1)!=1 ) o<<p.getA(1)<<"*x";
         if (p.getA(1)<0) o<<p.getA(1)<<"*x";
         if (p.getA(1)==1) o<<"x";}

     if (p.deg()>0){
         if (p.getA(0)>0) o<<" + "<<p.getA(0);
         if (p.getA(0)<0) o<<p.getA(0);}
     else {o<<p.getA(0); }

        o<<endl;
    }

    const Polynomial differential() const {
        Polynomial w;
        int k=deg();
        w.setA(k,0);

        for(int i=0;i<=k-1;i++){
           w.setA(i, getA(i+1)*(i+1));
            }
        return w;
    }

    vector<double> rationalRoots() const;
    vector<double> realRoots() const;
};

void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R);
const Polynomial gcd(const Polynomial &, const Polynomial &);



int main(){
    Polynomial p,w,s;
    cout<<"p - wielomian o wspolczynnikach [2, 0, -5, 4, 1]"<<endl;
    p.setA(4,2);
    p.setA(2,-5);
    p.setA(1,4);
    p.setA(0,1);

    cout<< "stopien wielomianu: "<<p.deg()<<endl;
    cout<< "wsploczynniki przy pierwszej potedze: " <<p.getA(1)<<endl;
    cout<< "wypisanie wielomianu: "<<endl;
    cout<<p<<endl;
    cout<<"wartosc wielomianu w punkcie 1,5:  "<< p.v(1.5)<<endl;
    s.setA(1,1);
    s.setA(0,5);
    cout<<"s - wielomian o wspolczynnikach [1, 5]"<<endl;
    cout<<"stopien wielomianu: "<< s.deg()<<endl;
    cout<<"wypisanie wielomianu: "<<endl;
    cout<<s<<endl;
    cout<<"miejsce zerowe w przedziale (-10,9): "<< s.findRoot(-10,9)<<endl;
    p+=s;
    cout<<"p+=s => p= "<<p<<endl;
    w=p-s;
    cout<<"p-s="<<w<<endl;
    cout<<"mnozenie"<<endl;
    cout<<p<<endl;
    cout<<" * "<< endl;
    cout<<s << endl;
    cout<<"=" <<p*s <<endl;

    cout<<"czy p=s?"<<endl;
    cout<<p<<" =?= "<<s<<endl;
    if(p==s) cout<<"rowne" <<endl;
    else cout<<"nierowne" <<endl;

    cout<<"pochodna wielomianu: "<<p<< "jest rowna "<<p.differential()<<endl;


}
