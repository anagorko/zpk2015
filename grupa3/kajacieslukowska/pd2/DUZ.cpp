#include <iostream>
using namespace std;

int main(){
    string pierwsza;
    string druga;
    char p;
    int i = 0;
    char wynik = '=';
    cin >> pierwsza >> p >> druga;

    if( pierwsza.length() > druga.length())
        wynik = '>';
    if( pierwsza.length() < druga.length())
        wynik = '<';
    if( pierwsza.length() == druga.length()) {
        while( i < pierwsza.length() && wynik == '=') {
            if( pierwsza[i] > druga[i]) {
                wynik = '>';
            }
            if( pierwsza[i] < druga[i]) {
                wynik = '<';
            }
            i = i + 1;
        }
    }

    if ( wynik == '>') {
        if( p == '!=' || p == '>' || p == '>=')
            cout << "TAK";
        else
            cout << "NIE";
    }
    if ( wynik == '<') {
        if( p == '!=' || p == '<' || p == '<=')
            cout << "TAK";
        else
            cout << "NIE";
    }
    if ( wynik == '=') {
        if( p == '=' || p == '>=' || p == '<=' )
            cout << "TAK";
        else
            cout << "NIE";
    }

}
