#include <iostream>
#include <iomanip>
using namespace std;

int main(){

int x;
cin >> x;
int t[x];

// uzupełnienie tablicy
for(int i=0; i<x; i++){
    cin >> t[i];
}

// wypisywanie liczb
for(int i=0; i<x; i=i+2){
    cout << t[i] << " ";
}
cout << endl;
for(int i=1; i<x; i=i+2){
    cout << t[i] << " ";
}
}
