#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    int suma =1;
if (a!=0)
    for (int i=1; i<=a; i++){
        suma = suma*i;   }
else
    suma=1;

cout << suma << endl;

}
