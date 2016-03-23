#include <iostream>
using namespace std;

int main() {
    int r;
    cin >> r;
    int a=r%19;;
    int b=r%4;
    int c=r%7;
    int d=0;
    int e=0;
    int f=0;
    int g=0;
    int dzien = 0;
    int miesiac = 0;
    if (r != 1954 && r != 1981 && r != 2076 && r != 2049 && r != 2133 && r != 2106) {
        if (r < 1900) {
            f=23;
            g=4;
        }
        else if (r>=1900 && r < 2100) {
            f=24;
            g=5;
        }
        else if (r >= 2100) {
            g=6;
            f=24;
        }
        d=(19*a+f)%30;
        e=(2*b + 4*c + 6*d + g)%7;
        if (d+e < 10) {
            dzien = 22 + d + e;
            miesiac = 3;
        }
        else {
            dzien = d + e - 9;
            miesiac = 4;
        }
    }
    else if (r == 1981 || r == 2076 || r == 2133){
        dzien = 19;
        miesiac = 4;
    }
    else if (r == 1954 || r == 2049 || r == 2106) {
        dzien = 18;
        miesiac = 4;
    }

    cout << dzien << " " << miesiac << endl;

}
