#include <iostream>
using namespace std;

int main() {
    int n,b;

    b=0;
    cin >> n  ;
    if (n<2) {return 0;}

    for (int i = 2; i*i <= n; i++) {
        if(n%i==0) {b=1;}
              }

    if (b==0) cout<<"pierwsza";
    else{cout<<"zlozona";}
}
