#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

class Polynomial
{
    /*a- wektor wsp�czynnik�w*/
    vector<double> a;

    double findRoot(double, double);

public:
    Polynomial();
    /*dodam jeszcze taki konstruktor, �e mo�na na wst�pie poda� wektor wsp�czynnik�w*/
    Polynomial(vector<double> coeff);

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

/*konstruktor tworzy wektor wsp�czynnik�w- wielomian st.0*/
Polynomial::Polynomial()
{
    a.push_back(0);
}

Polynomial::Polynomial(vector<double> coeff)
{
    a = coeff;
}

/*implementacja wypisywania na strumie� wymaga funkcji zwracaj�cej stopie� wielomianu*/
int Polynomial::deg() const
{
    for(int i = a.size() ; i >= 0 ;i--){
        if(i==0 || i==1){
            return 0;
        }
        else if(a[i-1] != 0){
            int degree = i-1;
            return degree;
        }
    }
}

/*wypisywanie na strumie� przy u�yciu nowej funkcji print*/
ostream & operator << (ostream &os, const Polynomial& q)
{
    /*wypisujemy kolejno wsp�czynnik i pot�g� x przy ka�dym elemencie wielomianu pocz�wszy od stopnia najwy�szego*/
    for(int i = q.deg(); i >= 0 ;i--){

        /*ZNAK przed wyrazem wielomianu dodajemy tylko je�li nie jest to pierwszy wyraz*/
        string sign;
        if(i < q.deg()){
            /*je�li liczba nieujemna, to na stream znak "+", w p.p. znak "-" doda si� sam*/
            if(q.a[i] >= 0){
                sign = " + ";
            }else{
                sign = " ";
            }
        }else{
            sign = "";
        }

        /*je�eli wielomian zerowy to po prostu wypluwamy 0*/
        if(q.deg() ==0 && q.a[i] ==0){
            os << sign << "0" << endl;
        }

        /*je�eli cz�� wielomianu stopnia 0*/
        if(i==0 && q.a[i] !=0){
            os << sign << q.a[i] << endl;
        }
        /*dla cz�ci stopnia jeden nie piszemy 1x^1 tylko po prostu x, wi�c te� rozpatrujemy osobno*/
        else if(i==1 && q.a[i] != 0 && q.a[i] != 1){
            os << sign << q.a[i] << "x";
        }
        else if(i==1 && q.a[i] == 1){
            os << sign << "x";
        }
        else {
            /*dodatkowy warunek- je�li wsp�czynnik = 0, to nie drukujemy tej cz�ci*/
            if(q.a[i] != 0 && q.a[i] != 1)
                os << sign << q.a[i] << "x^" << i ;
            if(q.a[i] == 1)
                os << sign << "x^" << i ;
        }
    }
    return os;
}

/*zmieniamy wsp�czynnik na warto�� value przy wyrazie wielomianu stopnia place*/
void Polynomial::setA(int place, double value)
{
    int actual_size = a.size();
    if(actual_size > 0){
        /*je�li dodajemy element wielomianu o stopniu wy�szym ni� ma wielomian, musimy rozszerzy� nasz wielomian
        i doda� element na ko�cu*/
        if(place >= actual_size){
            a.resize(place, 0);
            a.push_back(value);
        /*w przeciwnym wypadku zast�pujemy wsp�czynnik wielomianu*/
        }else{
            a[place] = value;
        }


    }

}

/*sprawdzamy wsp�czynnik przy wyrazie wielomianu stopnia place*/
double Polynomial::getA(int place) const
{
    return a[place];
}

/*policz warto�� wielomianu w punkcie x*/
double Polynomial::v(double x) const
{
    double wartosc = 0.0;
    for(int i = a.size() - 1; i >= 0 ;i--){
        wartosc += a[i] * pow(x,i);
    }
    return wartosc;
}

/*POCHODNA WIELOMIANU*/
const Polynomial Polynomial::differential() const {
        Polynomial diff;

        for(int i = 1; i <= this -> deg(); i++){
           diff.setA(i-1, i * this -> getA(i) );
        }

        return diff;
}


/*dodawanie wielomian�w, wykorzystanie operatora dodawania do obiektu += */
Polynomial& Polynomial::operator+=(const Polynomial& q){
    /*sprawdzamy czy stopie� pierwszego wielomianu jest mniejszy ni� dodawanego (q)
      je�li tak, to trzeba go rozszerzy� i tymczasowo postawi� zera przy wyrazach wy�szego stopnia*/
    if(deg() < q.deg()){
        a.resize(q.deg() + 1, 0);
    }
    for(int i = 0; i <= q.deg(); i++){
        a[i] = a[i] + q.getA(i);
    }
    return *this;

}

/*dodawanie wielomian�w, implementacja operatora + za pomoc� wcze�niej zaimplementowanego += */
const Polynomial Polynomial::operator+(const Polynomial &q) const{
    Polynomial c = *this;
    c += q;
    return c;
}

/*odejmowanie wielomian�w, wykorzystanie operatora odejmowania od obiektu -= */
Polynomial& Polynomial::operator-=(const Polynomial& q){
    /*sprawdzamy czy stopie� pierwszego wielomianu jest mniejszy ni� dodawanego (q)
      je�li tak, to trzeba go rozszerzy� i tymczasowo postawi� zera przy wyrazach wy�szego stopnia*/
    if(deg() < q.deg()){
        a.resize(q.deg() + 1, 0);
    }
    for(int i = 0; i <= q.deg(); i++){
        a[i] = a[i] - q.getA(i);
    }
    return *this;

}

/*odejmowanie wielomian�w, implementacja operatora - za pomoc� wcze�niej zaimplementowanego -= */
const Polynomial Polynomial::operator-(const Polynomial &q) const{
    Polynomial c = *this;
    c -= q;
    return c;
}

/*mno�enie wielomian�w, wykorzystanie operatora mnozenia obiektu *= */
Polynomial& Polynomial::operator*=(const Polynomial& q){
    /*stopie� wielomianu b�d�cego iloczynem wielomian�w jest sum� ich stopni
    zatem musimy zmieni� stopie� wyjsciowego wielomianu*/
    a.resize(deg() + q.deg() + 1, 0);
    Polynomial temppoly;
    temppoly.setA(deg() + q.deg()+1,1);

    for(int i = 0; i <= deg(); i++){
            for(int j = 0; j<= q.deg(); j++){
                double addVal = a[i] * q.getA(j);
                int addPlace =  i + j;
                double addTemppoly = addVal + temppoly.getA(addPlace);
                temppoly.setA(addPlace, addTemppoly);
            }

    }
    temppoly.setA(deg() + q.deg()+1,0);
    *this = temppoly;
    return *this;

}

/*dodawanie wielomian�w, implementacja operatora * za pomoc� wcze�niej zaimplementowanego *= */
const Polynomial Polynomial::operator*(const Polynomial &q) const{
    Polynomial c = *this;
    c *= q;
    return c;
}

/*POR�WNYWANIE WIELOMIAN�W*/

bool Polynomial::operator==(const Polynomial &q) const
{
    /*je�eli stopnie wielomian�w to od razu zwracamy FALSE*/
    if(deg() != q.deg()){
        return false;
    }else{
        for(int i = 0; i <= deg(); i++){
            if(a[i] != q.getA(i)){
                return false;
            }
        }
        return true;
    }
}

bool Polynomial::operator!=(const Polynomial &q) const
{
    return !(*this == q);
}


/*DZIELENIE WIELOMIANU PRZEZ WIELOMIAN W/P*/
void div(const Polynomial &W, const Polynomial &P, Polynomial &Q, Polynomial &R){
    Q.setA(0,0);
    Polynomial Dtemp;
    Polynomial Wtemp;
    Wtemp = W;
    Polynomial Ptemp;
    Ptemp = P;

    if(W.deg() < P.deg()){
        R = W;
        Q.setA(0,0);
    }else{
        while (Wtemp.deg() >= Ptemp.deg() && Wtemp.deg() <= 6){
            /*wielomian Dtemp jest tworzony tymczasowo jako to co b�dziemy odejmowa� w kolejnych krokach od wielomianu*/
            for(int i=0; i< Wtemp.deg() + 1; i++){
                Dtemp.setA(i, 0);
            }

            for(int i=0; i< Ptemp.deg() + 1; i++){
                Dtemp.setA(i + Wtemp.deg() - Ptemp.deg(), Ptemp.getA(i));
            }
            for(int i=Wtemp.deg() +1; i< Dtemp.deg() + 1; i++){
                Dtemp.setA(i, 0);
            }

            /*wielomian q czyli wynik dzielenia ma stopien W-P
            w kolejnych krokach dodajemy do niego sk�adniki dziel�c czynnik przy wyrazie najwy�szego stopnia wiel. W
            przez czynnik przy wyrazie najwy�szego stopnia wielomianu Dtemp, taki czynnik ma stopie� W-P*/
            Q.setA(Wtemp.deg() - Ptemp.deg(), Wtemp.getA(Wtemp.deg()) / Dtemp.getA(Dtemp.deg()));
            /*przeliczamy Dtemp �eby sprawdzi� ile razy mamy go odj�c*/
            for(int i=0; i< Dtemp.deg() + 1; i++){
                Dtemp.setA(i, Dtemp.getA(i) * Q.getA(Wtemp.deg() - Ptemp.deg()));
            }
            /*odejmujemy Dtemp od Wtemp i powtarzamy procedur� od nowa
            a� stopie� wielomianu Wtemp b�dzie ni�szy ni� Dtemp
            wtedy pozosta�o�� b�dzie reszt� R*/
            Wtemp -= Dtemp;
        }
        R = Wtemp;
    }


}

/*NWD*/
const Polynomial gcd(const Polynomial &A, const Polynomial &B){
    Polynomial Q;
    Polynomial R;
    /*robimy kopie, bo const nie mo�emy zmienia�*/
    Polynomial Acopy;
    Polynomial Bcopy;
    /*zapewniamy sobie, �eby dzieli� wielomian wi�kszego stopnia przez wielm ni�szego st*/
    if(A.deg() < B.deg()){
        Acopy = B;
        Bcopy = A;
    }else{
        Acopy = A;
        Bcopy = B;
    }
    div(Acopy, Bcopy, Q, R);
    Bcopy = R;
    /*p�tla jak dla tardycyjnego wyszukiwania NWD dla liczb naturalnych*/
    while(R.deg() != 0 && R.getA(0)!= 0){
        Acopy = Bcopy;
        Bcopy = R;
        div(Acopy, Bcopy, Q, R);
    }
    return Bcopy;

}


int main()
{

    Polynomial poly1 ;
    cout << "Wielomian 0 jest stopnia: " << poly1.deg() << endl;;
    cout << "Wielomian 0: " << poly1 <<endl;
    poly1.setA(0, 1);
    cout << "Wielomian po operacji setA(0,1): " << poly1 <<endl;
    poly1.setA(1, -2);
    cout << "Stopie� po setA(1,-2): " << poly1.deg() << endl;;
    cout << "Wielomian po setA(1,-2): " << poly1 <<endl;
    poly1.setA(5, 1);
    cout << "Stopie� po setA(5, 4): " << poly1.deg() << endl;;
    cout << "Wielomian: " << poly1 <<endl;
    poly1.setA(0, 0);
    cout << "Stopie� po setA(0,0): " << poly1.deg() << endl;;
    cout << "Wielomian " << poly1 <<endl;
    cout << "Wielomian getA(0) " << poly1.getA(0) <<endl;
    cout << "Wielomian getA(1) " << poly1.getA(1) <<endl;
    cout << "Wielomian getA(2) " << poly1.getA(2) <<endl;
    cout << "Wielomian getA(3) " << poly1.getA(3) <<endl;
    cout << "Wielomian getA(5) " << poly1.getA(5) <<endl;
    cout << "Wielomian warto�� w punkcie 5.0 v(5) " << poly1.v(5.0) << endl;
    cout << "Wielomian warto�� w punkcie -5.0 v(-5.0) " << poly1.v(-5.0) << endl;


    Polynomial poly2;
    poly2.setA(5, 4);
    cout << "Wielomian 2: " << poly2 <<endl;
    cout << "DODAWANIE " << endl;
    poly1 += poly2;
    cout << "Wielomian1+=Wielomian2 " << poly1 <<endl;
    Polynomial poly3 = poly1 + poly2;
    cout << "Wielomian3=Wielomian1+Wielomian2 " << poly3 <<endl;

    cout << "ODEJMOWANIE " << endl;
    cout << "Wielomian3 " << poly3 <<endl;
    poly3 -= poly2;
    cout << "Wielomian3-=Wielomian2 " << poly3 <<endl;
    Polynomial poly4 = poly3 - poly2;
    cout << "Wielomian4=Wielomian3-Wielomian2 " << poly4 <<endl;

    cout << "MNOZENIE " << endl;
    Polynomial polyCZ1;
    polyCZ1.setA(2,2);
    polyCZ1.setA(1,-4);
    polyCZ1.setA(0,5);
    cout << "WielomianCZ1 " << polyCZ1 <<endl;
    Polynomial polyCZ2;
    polyCZ2.setA(1,1);
    polyCZ2.setA(0,1);
    cout << "WielomianCZ2 " << polyCZ2 <<endl;
    Polynomial polyMN = polyCZ1 * polyCZ2;
    cout << "WielomianMN=WielomianCZ1*WielomianCZ2 " << polyMN <<endl;
    polyCZ1 *= polyCZ2;
    cout << "WielomianCZ1 *= WielomianCZ2 " << polyCZ1 <<endl;

    cout << "POROWNYWANIE " << endl;
    polyCZ2 = polyCZ1;
    cout << "czy wielomianCZ1 == wielomianCZ2  " << endl;
    if(polyCZ1 == polyCZ2){
        cout << "wielomiancz1 == wielomianCZ2 "  <<endl;
    }
    cout << "czy wielomianCZ1 == wielomian1  " << endl;
    if(polyCZ1 == poly1){
        cout << "wielomianCZ1 == wielomian1 "  <<endl;
    }else{
        cout << "NIE"<< endl;
    }
    cout << "czy wielomianCZ1 != wielomian1  " << endl;
    if(polyCZ1 != poly1){
        cout << "polyCZ1 != poly1 "  <<endl;
    }else{
        cout << "polyCZ1 == poly1 "  <<endl;
    }

    /*deklaracja wielomainu przez wektor*/
    vector<double> t;
    t.push_back(1);
    t.push_back(2);
    t.push_back(0);
    t.push_back(0);
    t.push_back(-3);
    t.push_back(0);
    t.push_back(1);
    Polynomial polvec(t);
    cout << "polvec" << polvec <<endl;

    /*DZIELENIE WIELOMIAN�W*/
    const Polynomial Dzielony(t);
    cout << "wielomian Dzielony "<< Dzielony <<endl;
    vector<double> s({-1, 0, 1});

    const Polynomial Dzielnik(s);
    cout << "wielomian Dzielnik "<< Dzielnik <<endl;

    Polynomial Q1;
    Polynomial R1;

    div(Dzielony, Dzielnik, Q1, R1);
    cout << "czesc ca�kowita Q = " << Q1 <<endl;
    cout << "reszta R = " << R1 <<endl;

    /*POCHODNA*/
     cout << "Pochodna reszty: = " << R1.differential() <<endl;
     cout << "Pochodna czesci calkowitej Q: = " << Q1.differential() <<endl;

     /*NWD wielomian�w*/
    cout << "NWD "  <<endl;
    Polynomial Q2;
    Polynomial R2;
    vector<double> a({-1,0,1});
    Polynomial A(a);
    cout << "Wielomian A: = " << A <<endl;
    vector<double> b({-1,0,0,1});
    Polynomial B(b);
    cout << "Wielomian B: = " << b <<endl;
    cout << "NWD:  = " << gcd(B, A) <<endl;

}
