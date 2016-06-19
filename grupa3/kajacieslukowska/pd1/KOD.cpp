#include <iostream>
using namespace std;

int main(){
    char a;
    char b;
    cin >> a >> b;
    int kod;


    if ( int(b) < 58) {
        kod = 16*(int(a) - 48) + int(b) - 48;
    }
    else {
        kod = 16*(int(a) - 48) + int(b) - 55;
    }

    cout << kod << endl;
    cout << char(kod) << endl;

}
