#include <iostream>
#include <math.h>
using namespace std;

int main(){

int n;
cin >> n;

bool pierwsza = true;

for(int i=2; i<=sqrt(n); i++){
    if(n%i==0)
        pierwsza = false;
        break;
}

if(pierwsza)
    cout << "pierwsza" << endl;
if(pierwsza == false)
    cout << "zlozona" << endl;

}
