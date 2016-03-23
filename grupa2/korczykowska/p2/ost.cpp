#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


int main() {
   int n;
   cin >> n;
   int ost_cyfra;

if (n==0)
    cout << pow(2, n) << endl;
    
else{
        switch(n%4){
        case 0:
            ost_cyfra = 6;
            break;
        case 1:
            ost_cyfra = 2;
            break;
        case 2:
            ost_cyfra = 4;
            break;
        case 3:
            ost_cyfra = 8;
            break;}
cout << ost_cyfra <<endl;
}
}
