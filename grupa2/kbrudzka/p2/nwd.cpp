# include<iostream>
using namespace std;

int NWD(int a, int b) {

int c=a%b;
while (c!=0) {

a=b; b=c; c=a%b;
}

return b;
}

int main(){

int n;
cin >> n;
int t[n];

for (int i=0; i<n; i++)
cin >> t[i];

int nwd=t[0];

for (int k=1; k<n; k++){

nwd=NWD(t[k],nwd); /* teraz liczba a bedzie nwd z a i b natomiast liczba b bedzie pierwszy element wczytanej tablicy (nazwany nwd)*/
}

cout << nwd;


}
