#include<iostream>

using namespace std;


int main(){
int n;
cin >> n;
int liczby[n];

for (int i=0;i<n;i++){
 cin >> liczby[i];   
}

for (int i=0;i<n;i=i+2) {
    cout << liczby[i] << ' ';
}
 cout << endl;
for (int i=1;i<n;i=i+2) {
    cout << liczby [i] << ' ';   
}
}
