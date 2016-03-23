#include <iostream>
using namespace std;

int main()
{
int i;
cin >> i;

    while(i!=1) // dopoki jest w tej czesci petli to zatrzyma sie
    {
    if (i%2 == 0)
    i = i/2;

    else
    {
    cout << "Nie" << endl;
    return 0;
    }
   // i = 3 * i + 3; jesli wpadlaby do tej petli, to juz sie nie zatrzyma - mozna ja pominac i od razu wypisac "NIE"
    }
cout << "Tak" << endl;
}
