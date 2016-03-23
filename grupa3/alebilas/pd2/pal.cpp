#include <iostream>
using namespace std;

int main(){

string x;
cin >> x;

int len = x.length();
bool czy_pal = true;

for(int i=0; i<len; i++){
    if(x[i]!=x[len-1-i])
        czy_pal=false;
}

if(czy_pal)
    cout << "TAK" << endl;
if(czy_pal == false)
    cout << "NIE" << endl;

}
