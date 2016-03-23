#include<iostream>

using namespace std;


int main(){
int dni;
int cena;
int d1 = -1;
int d2 = -1;

cin >> dni >> cena;
int i[dni];
for (int j=0;j<dni;j++) {
    cin >> i[j];
}

for (int j=0;j<dni;j++) {
    if (i[j]==cena && d1 == -1)
        d1 = j+1;
    if (i[j]==cena)
        d2 = j+1;
}
cout << d1 << ' ' << d2;
}
