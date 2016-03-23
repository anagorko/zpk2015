#include <iostream>
using namespace std;

int main()
{
    int r;
    int a, b, c, d, e, aa, bb;
    cin >> r;

    a = r%19;
    b = r%4;
    c = r%7;

    // dla XIX wieku
    if(r>=1800 && r<1900){
        aa=23;
        bb=4;
    }
    // dla XX i XXI wieku
    if(r>=1900 && r<2100){
        aa=24;
        bb=5;
    }
    // dla XXII wieku
    if(r>=2100 && r<2200){
        aa=24;
        bb=6;
    }

    d=(a*19+aa)%30;
    e=(2*b+4*c+6*d+bb)%7;

    // wyjatek I rodzaju
    if(r==1981 || r==2076 || r==2133){
        cout << 19 << " " << 4 << endl;
    }
    // wyjatek II rodzaju
    if(r==1954 || r==2049 || r==2106){
        cout << 18 << " " << 4 << endl;
    }
    // jezeli data nie wypada powyzej 31 marca i nie zachodza powyzsze wyjatki
    if(r!=1981 && r!=2076 && r!=2133 && r!=1954 && r!=2049 && r!=2106 && (d+e)<10){
        cout << d+e+22 << " " << 3 << endl;
    }
    // jezeli data wypada poza 31 marca i nie zachodza powyzsze wyjatki
    if(r!=1981 && r!=2076 && r!=2133 && r!=1954 && r!=2049 && r!=2106 && (d+e)>=10){
        cout << d+e-9 << " " << 4 << endl;
    }
}
