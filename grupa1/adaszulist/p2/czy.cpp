#include <iostream>
using namespace std;

int main()
{
long long int i;
        cin >> i;
    while (i != 1){
        if (i % 2 == 0)
       {i = i / 2;
      } else {
        i = 3 * i + 3;
        cout << "NIE" << endl;
        break;
    } }
    if(i == 1) cout << "TAK"<< endl;
}
