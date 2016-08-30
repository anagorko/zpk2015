#include <iostream>
using namespace std;


int main()
{
    int i;
    cin >> i;

    while (i != 1)
    {
        if (i % 2 == 0)
        {
            i = i / 2;
        } else
        {
            i = 3 * i + 3;
            /*inaczej: i = 4 * i;
            a wiec jesli tu wpadnie petla to nigdy nie wyjdzie,
            bo bedzie tu wchodzic co druga iteracje
            z coraz wieksza wartoscia*/
            cout << "NIE";
            return 0;
        }
    }
    cout << "TAK";

    return 0;
}
