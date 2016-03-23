#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;


int main() {
int n;
cin >> n;
int o[n];

for (int i=0;i<n;i++){
    cin >> o[i];
}

int wynik[6] = {0,0,0,0,0,0};

for (int i=0;i<n;i++) {
    switch (o[i]){
    case 1:
        wynik[0]++;
        break;
    case 2:
        wynik[1]++;
        break;
    case 3:
        wynik[2]++;
        break;
    case 4:
        wynik[3]++;
        break;
    case 5:
        wynik[4]++;
        break;
    case 6:
        wynik[5]++;
        break;}
}
cout << wynik[0] << ' ' << wynik[1] << ' ' << wynik[2] << ' ' << wynik[3] << ' ' << wynik[4] << ' ' << wynik[5];
}
