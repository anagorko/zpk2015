#include <iostream>
using namespace std;

int main(){

int long a, i=2;
bool pier = true;
cin>>a;
while(pier==true && i<a){
    if(a%i==0)
        pier=false;
        i++;
}

if(pier)
    cout << "pierwsza" << endl;
else
    cout << "zlozona" << endl;


}
