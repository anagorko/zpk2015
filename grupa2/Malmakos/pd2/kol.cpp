#include <iostream>;
#include <iomanip>;
#include <cmath>;
using namespace std;


int main(){

    double promien;
    double obwod;
    double pole;
    cin>> promien;

    obwod = 2*M_PI*promien;
    pole = M_PI*promien*promien;
cout << setprecision(3)<<fixed;
cout << pole <<endl;
cout << obwod <<endl;

}
