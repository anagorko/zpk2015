#include <iostream>
using namespace std;

int main(){
    char a, b;
    int kod;
    cin >> a >> b;
    if (b >= 'A' && b <= 'F'){
        kod = 16 * (a-48) + b - 55;
        cout << kod << endl << (char)kod << endl;
}
    else{
        kod = 16 * (a-48) + b - 48;
        cout << kod << endl << (char)kod << endl;
    }
}
