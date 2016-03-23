#include <iostream>
#include <string>

using namespace std;

bool wieksza (string pierwsza, string druga)
{
    if (pierwsza.length() > druga.length())
        return true;
    if (pierwsza.length() < druga.length())
        return false;
    // jak tu doszlismy to sa takie same dlugosci
    for (int i=0; i < pierwsza.length(); i++)
    {
        if (pierwsza[i] < druga[i])
            return false;
        if (pierwsza[i] > druga[i])
            return true;
    }
    return false; // takie same
}

int main()
{
    string pierwsza, znak, druga;
    cin >> pierwsza >> znak >> druga;
    bool wynik = false;
    if (znak.compare(">") == 0)
        wynik = wieksza (pierwsza, druga);
    if (znak.compare("<") == 0)
        wynik = wieksza (druga, pierwsza);
    if (znak.compare(">=") == 0)
        wynik = !wieksza(druga, pierwsza);
    if (znak.compare("<=") == 0)
        wynik = !wieksza(pierwsza, druga);
    if (znak.compare("==") == 0)
        wynik = !wieksza(pierwsza, druga) && !wieksza(druga, pierwsza);
    if (znak.compare("!=") == 0)
        wynik = wieksza (pierwsza, druga) || wieksza (druga, pierwsza);

    if (wynik == true)
        cout<<"TAK"<<endl;
    else
        cout<<"NIE"<<endl;

    return 0;
}
