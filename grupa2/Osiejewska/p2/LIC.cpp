#include <iostream>
using namespace std;

int main(){
int a;
cin >> a;
int suma=0;
for (int i=2; i<=a; i++){
if (a%i==0)
    suma+=suma+1;
}
if (suma==1)
    cout << "pierwsza" << endl;
else
    cout << "zlozona" << endl;

}
