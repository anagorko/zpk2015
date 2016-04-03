#include<iostream>
using namespace std;

int main(){
    string slowo;
    cin >> slowo;

    int d = slowo.size();
    bool palindrom=true;

    for(int i=0, j=d-1; i<d && j>=0; i++, j--){
        if(slowo[i]!=slowo[j]){
            palindrom = false;
            break;
        }
    }
    if(palindrom)
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
}
