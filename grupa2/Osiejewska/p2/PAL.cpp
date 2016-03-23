#include <iostream>
using namespace std;

int main(){
string slowo;
cin >> slowo;

int d = slowo.size();
bool prawda=true;
for (int i=0, j=d-1; i<d && j>=0; i++, j--){
    if (slowo[i]!=slowo[j]){
        prawda=false;
        break;
    }
    else
        prawda=true;
}

 if (prawda)
    cout << "TAK" << endl;
 else
    cout << "NIE" << endl;
}
