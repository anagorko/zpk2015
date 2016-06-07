#include <iostream>
using namespace std;

int main(){
    int x;
    int y;
    int z;
    cin >> x >> y >> z;

    if((x>y && y>z) || (x>z && z> y))
        if(y+z>x)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    else if ((y>x && x>z) || (y>z && z> x))
        if(z+x>y)
            cout << "TAK" << endl;
        else
            cout << "NIE" << endl;
    else if (x+y>z)
          cout << "TAK" << endl;
        else
            cout << "NIE" << endl;



}
