#include <iostream>
#include<string>
using namespace std;

int main(){
string a, znak, b;
cin >> a >> znak >> b;
int mw = 0;
    if (a.size() > b.size()) 
        mw = 1;
    else if (a.size() < b.size()) 
        mw = 2;
    else {
        for (int i=0; i < a.size(); i++)
        {
            if(a[i] > b[i]){
                mw = 1;
                break;
            }
            else if(a[i] < b[i]){
                mw = 2;
                break;
            }
        }
}
if(znak == "==" && mw == 0)
    cout << "TAK" << endl;
else if(znak == "==")
    cout << "NIE" << endl;

if(znak == "!=" && mw == 0)
    cout << "NIE" << endl;
else if(znak == "!=")
    cout << "TAK" << endl;

if(znak == "<" && mw == 2)
    cout << "TAK" << endl;
else if(znak == "<")
    cout << "NIE" << endl;


if(znak == ">" && mw == 1)
    cout << "TAK" << endl;
else if(znak == ">")
    cout << "NIE" << endl;


if(znak == "<=" && mw != 1)
    cout << "TAK" << endl;
else if(znak == "<=")
    cout << "NIE" << endl;


if(znak == ">=" && mw != 2)
    cout << "TAK" << endl;
else if(znak == ">=")
    cout << "NIE" << endl;
return 0;
}
