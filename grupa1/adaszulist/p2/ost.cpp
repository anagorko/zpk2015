#include <iostream>
#include <math.h>

using namespace std;

int main(){
long long int a, pot, ost;
cin >> a;

if(a > 62) {
    a = a % 4;
        if(a == 0){
            a = 4;
        }
}
pot = pow (2,a);
ost = pot % 10;
cout << ost;

return 0;
}
