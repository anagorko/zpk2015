#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){

int x;
int y;

int pierwszy=-1;
int ostatni=-1;

cin >> x >> y;

int t[x];

for(int i=0; i<x; i++)
    cin >> t[i];

for(int i=0; i<x; i++){
    if(t[i]==y && pierwszy==-1){
        pierwszy=i+1;
        ostatni=pierwszy;
    }
    else if(t[i]==y)
        ostatni=i+1;
}
cout << pierwszy << " " << ostatni << endl;
}
