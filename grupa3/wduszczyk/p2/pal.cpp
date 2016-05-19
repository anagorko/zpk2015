// Example program
#include <iostream>
#include <string>
#include <math.h>  

using namespace std;

int main(){
    string slowo;
    cin >> slowo;
    int dl = slowo.size();
    bool palindrom = true;
    for (int i = 0; i <= dl/2; i++){
        if (slowo[i] != slowo[dl - 1 - i])
            palindrom = false;
    }
    if (palindrom)
        cout << "TAK" <<  endl;
    else
        cout << "NIE" <<  endl;



}
	