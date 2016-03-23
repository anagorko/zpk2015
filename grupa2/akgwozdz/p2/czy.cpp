#include <iostream>
using namespace std;

int main()
{
    int i;
    cin >> i;
    while (i != 1)
     if (i%2 == 0)
        {i = i/2;
        {
            if (i == 1)
                {
                cout << "TAK" << endl;
                break;
                }
            else if (i == 3)
                {
                cout << "NIE" << endl;
                break;
                }
        }
        }
     else
        i = 3*i + 3;
}
