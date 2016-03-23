#include <iostream>
#include <string>
using namespace std;

int main()
{
    bool pal =true;
    string wyraz;
    int dlugosc, i;
    cin >> wyraz;
    dlugosc=wyraz.size();
    for (i = 0; i<=dlugosc-1; i++){
        if(wyraz[i]==wyraz[dlugosc-1])
            dlugosc--;
        else
            pal = false;
    }

    if (pal == true)
        cout << "TAK" << endl;
    else
        cout << "NIE";
}
