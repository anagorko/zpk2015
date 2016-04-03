#include<iostream>
#include<string>
using namespace std;

int main(){
    string a, b, znak;
    cin >> a >> znak >> b;

    int length_a = a.length();
    int length_b = b.length();

    bool a_wieksza = false;
    bool b_wieksza = false;
    bool rowne = true;

    if(length_a > length_b){
        a_wieksza = true;
        rowne = false;
    }
    else if(length_a < length_b){
        b_wieksza = true;
        rowne = false;
    }
    else {
        for(int i=0; i<length_a; i++){
            if(a[i]>b[i]){
                a_wieksza = true;
                rowne = false;
                break;
            }
            else if(a[i]<b[i]){
                b_wieksza = true;
                rowne = false;
                break;
            }
        }
    }
    if(znak == "==" && rowne == true)
        cout << "TAK" << endl;
    else if(znak == "==")
        cout << "NIE" << endl;

    if(znak == "!=" && rowne == true)
        cout << "NIE" << endl;
    else if(znak == "!=")
        cout << "TAK" << endl;

    if(znak == "<" && b_wieksza == true)
        cout << "TAK" << endl;
    else if(znak == "<")
        cout << "NIE" << endl;

    if(znak == ">" && a_wieksza == true)
        cout << "TAK" << endl;
    else if(znak == ">")
        cout << "NIE" << endl;

    if(znak == ">=" && b_wieksza == false)
        cout << "TAK" << endl;
    else if(znak == ">=")
        cout << "NIE" << endl;

    if(znak == "<=" && a_wieksza == false)
        cout << "TAK" << endl;
    else if(znak == "<=")
        cout << "NIE" << endl;
}
