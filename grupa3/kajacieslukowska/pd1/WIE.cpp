#include <iostream>
using namespace std;

int main(){
    int r;
    int a;
    int b;
    cin >> r;
    bool wyjatek = false;

    if( r > 1799 && r <=1899) {
        a = 23;
        b = 4;
    }
    if( r > 1899 && r <=2099) {
        a = 24;
        b = 5;
    }
    if( r > 2099 && r <=2199) {
        a = 24;
        b = 6;
    }

    int wynik = (2*(r%4)+4*(r%7)+6*(((r%19)*19+a)%30)+b)%7 + ((r%19)*19+a)%30;

    if( r == 1981 || r == 2076 || r == 2133) {
        wyjatek = true;
        cout << 19 << " " << 4 << endl;
    }
    if( r == 1954 || r == 2049 || r == 2106) {
        wyjatek = true;
        cout << 18 << " " << 4 << endl;
    }
    if( wynik < 10 && wyjatek == false) {
        cout << 22 + wynik << " " << 3 << endl;
    }
    if( wynik >= 10 && wyjatek == false) {
        cout << wynik - 9 << " " << 4 << endl;
    }
}

