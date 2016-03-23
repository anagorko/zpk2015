#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){

int n;
int ostatnia;

cin >> n;

if(n==0)
    ostatnia=1;
else if(n%4==1)
    ostatnia=2;
else if(n%4==2)
    ostatnia=4;
else if(n%4==3)
    ostatnia=8;
else if(n%4==0)
    ostatnia=6;

cout << ostatnia << endl;
}
