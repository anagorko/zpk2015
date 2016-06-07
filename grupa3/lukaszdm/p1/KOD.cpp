
#include <iostream>
using namespace std;

int main() {
int kod;
char litera, x, y;

cin >> x >> y;
if((int)y>64) {
    kod = ((int)x - 47) * 16 + (int)y-55;
    litera=(char)kod;
}
else {
    kod = ((int)x - 47) * 16 + (int)y-47;
    litera=(char)kod;
}
cout << kod << endl;
cout << litera << endl;
}
