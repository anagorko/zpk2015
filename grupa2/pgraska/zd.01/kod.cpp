#include <iostream>
using namespace std;

int main() {
int wynik;
char cyfra1, cyfra2;
cin >> cyfra1 >> cyfra2;
if(cyfra2 >= 65 && cyfra2 <= 70)
    wynik = (cyfra1 - 48) * 16 + cyfra2 - 55;
else
    wynik = 16 * (cyfra1 - 48) + cyfra2 - 48;

cout << wynik << endl;
cout << char(wynik) << endl;
}
