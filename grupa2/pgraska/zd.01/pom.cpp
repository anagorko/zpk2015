#include <iostream>
using namespace std;

int main() {
    int wynik_pomiaru = 0;
    int wczesniejszy_odczyt = 0;
    int ostatni_odczyt = 0;
        while (ostatni_odczyt != -1) {
            cin >> ostatni_odczyt;
            if (ostatni_odczyt > wczesniejszy_odczyt)
            wynik_pomiaru++;
            wczesniejszy_odczyt = ostatni_odczyt;
        }
    cout << wynik_pomiaru << endl;
}
