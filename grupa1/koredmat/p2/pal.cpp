#include <iostream>
using namespace std;

int main () {
string slowo;
cin >> slowo;

bool pal;
int i=slowo.length();
while (i>0) {
        i--;
        if (slowo[i]!=slowo[slowo.length()-i-1]) {pal=false;}
        }
if (pal) {cout << "TAK";}
else {cout << "NIE";}
}

