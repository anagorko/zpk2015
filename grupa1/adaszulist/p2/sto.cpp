#include <iostream>
using namespace std;

int main(){
int a,b,k;
int ilosc_a = 0;
int ilosc_b = 0;
int ilosc;

cin >> a >> b >> k;

if (b < 2 * k) {
    ilosc_a = a / k;
}
else {
    ilosc_a = a / k;
    ilosc_a = 2 * ilosc_a;
}

if (b > 2 * k) {
    if (a < 2 * k) {
      ilosc_b = b / k;
      ilosc_b -= 2;
    }
    else {
        ilosc_b = b / k;
        ilosc_b = ilosc_b * 2-4;
    }
}
ilosc = ilosc_a + ilosc_b;
cout << ilosc;
return 0;
}
